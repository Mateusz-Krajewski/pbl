#include <Arduino.h>
#include <Pixy2.h>
#include <PIxy2CCC.h>
#include <SPI.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Ultrasonic.h>
#include "../lib/motorDriver.h"
#include "../lib/distanceSensor.h"
#include "../lib/pickupMotor.h"
#include "../lib/pixmeDriver.h"

namespace {
  constexpr auto DISTANCE = 25;

  constexpr auto RIGHT_TRIG = 29;
  constexpr auto RIGHT_ECHO =  28;
  constexpr auto LEFT_ECHO = 32;
  constexpr auto LEFT_TRIG = 33;
}

namespace {
  constexpr auto ARM_PIN = 4;
  constexpr auto HAND_PIN = 3;
}

enum modes { 
  SEARCHING, 
  GOTOTHECUBE,
  GETCLOSERTOTHECUBE,
  PICKUP,
  ERROR
};
enum TURN {
  RIGHT,
  LEFT,
  NO
};

ArmController armController;
MotorDriver motor;
Pixy2 pixy;
//PixyController pixy;
//DistanceSensor left_sonic(RIGHT_TRIG, RIGHT_ECHO);
DistanceSensor right_sonic(LEFT_TRIG, LEFT_ECHO);

modes mode = modes::SEARCHING;

class ModesClass {
 private:
  TURN last_turn;
  void print(Block *blocks, int size) {
    Serial.println("--------------------------------------------");
    Serial.print("M_x");
    Serial.println(blocks[0].m_x);
    Serial.print("M_y");
    Serial.println(blocks[0].m_y);
    Serial.println("--------------------------------------------");
    Serial.println("--------------------------------------------");
    Serial.println("--------------------------------------------");
    Serial.println("--------------------------------------------");
  }
  bool cubeIsFounded() {
    for (int i = 0; i < pixy.ccc.numBlocks; i++) {
      if (pixy.ccc.blocks[i].m_signature == 1 || pixy.ccc.blocks[i].m_signature == 2) {
        return true;
      }
    }
      return false;
   }
  void tryNotCrashWall() {
    int rightMiddle_distance = right_sonic.read();
    //int leftMiddle_distance = left_sonic.read();
    Serial.print("right:");
    Serial.println(rightMiddle_distance);
    // Serial.print("left:");
    // Serial.println(leftMiddle_distance);
    Serial.println("---------------------------------------");
    if ((rightMiddle_distance > DISTANCE) ) {
      motor.gofront();
      last_turn = TURN::NO;
    } else {
      if ( last_turn == TURN::RIGHT) {
        motor.turnright();
        last_turn = TURN::RIGHT;
      } else {
        motor.turnleft();
        last_turn = TURN::LEFT;
      }
    }
  }
 public:
  ModesClass() {
    last_turn = TURN::NO;
  }
  void Searching() {
    if(this->cubeIsFounded()) {
      mode = modes::GOTOTHECUBE;
    } else {
    this->tryNotCrashWall();
    }
  }
bool GOTHECUBE(){
  //Check if cube lost
  if(pixy.ccc.numBlocks){
    if(pixy.ccc.blocks[0].m_x <= 130){//if detected object is left of center x
      motor.turnleft_Alignment();
    } else if(pixy.ccc.blocks[0].m_x >= 140){//if detected object i right of center x
      motor.turnright_Alignment();
    } else {
      mode = modes::GETCLOSERTOTHECUBE;
      motor.stop();
      return true;
    }
  } else {
    mode = modes::SEARCHING;
    return false;
  }
}
void GO_CLOSER() {
  int i = true;
  bool need_pickup = true;
  auto value_m_y =0;
  if (pixy.ccc.numBlocks) {
    value_m_y = pixy.ccc.blocks[0].m_y;
    while (value_m_y > 190) {
      value_m_y = pixy.ccc.blocks[0].m_y;
      if (pixy.ccc.blocks[0].m_y > 190) {
        motor.goback();
      }
    }
  while (value_m_y < 175 ) {
    if (i == 2) {
    this->GOTHECUBE();
    i = 0;
    } else {
      i +=1;
    }
    motor.gofront(SPEED_t::KMIDLE);
    pixy.ccc.getBlocks();
    if (pixy.ccc.numBlocks > 0) {
      value_m_y = pixy.ccc.blocks[0].m_y;
    } else {
      need_pickup = false;
      mode = modes::SEARCHING;
      break;
    }
  };
  if (need_pickup) {
  motor.stop();
  mode = modes::PICKUP;
  } else {
    mode = modes::SEARCHING;
  }
}

};

ModesClass controller;



void setup() {
  Serial.begin(115200);
  armController.setup(HAND_PIN, ARM_PIN);
  motor.setup();
  pixy.init();
  pixy.setLamp(1,1);
  mode = modes::SEARCHING;
}

void loop() {
  pixy.ccc.getBlocks();
  if (mode == modes::SEARCHING) {
    controller.Searching();
  }
  else if (mode == modes::GOTOTHECUBE) {
    controller.GOTHECUBE();
  } else if (mode == modes::GETCLOSERTOTHECUBE) {
    controller.GO_CLOSER();
  } else if (mode == modes::PICKUP) {
    for (int i=0; i< 5; i++) {
    pixy.ccc.getBlocks();
    controller.GOTHECUBE();
    }
    armController.catchACube();
    motor.goback();
    armController.catchACube2();
    mode = modes::SEARCHING;
  }
}