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
//Pixy2 pixy;
PixyController pixy;
DistanceSensor left_sonic(RIGHT_TRIG, RIGHT_ECHO);
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
    Serial.print("M_y");
    Serial.println(blocks[0].m_index);
    Serial.println("--------------------------------------------");
    Serial.println("--------------------------------------------");
    Serial.println("--------------------------------------------");
    Serial.println("--------------------------------------------");
  }
  bool cubeIsFounded() {
      return pixy.CubeInView();
   }
  void tryNotCrashWall() {
    int rightMiddle_distance = right_sonic.read();
    int leftMiddle_distance = left_sonic.read();
    Serial.print("right:");
    Serial.println(rightMiddle_distance);
    Serial.print("left:");
    Serial.println(leftMiddle_distance);
    Serial.println("---------------------------------------");
    if ((rightMiddle_distance > DISTANCE) && (leftMiddle_distance > DISTANCE)) {
      motor.gofront();
      last_turn = TURN::NO;
    } else if(rightMiddle_distance < leftMiddle_distance){
      if ( last_turn == TURN::RIGHT) {
        motor.turnright();
        last_turn = TURN::RIGHT;
      } else {
        motor.turnleft();
        last_turn = TURN::LEFT;
      }
    } else {
      if (last_turn == TURN::LEFT) {
        motor.turnleft();
        last_turn = TURN::LEFT;
      } else {
      motor.turnright();
      last_turn = TURN::RIGHT;
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
  int size = 0;
  auto blocks = pixy.GetBlocks(size);
  this->print(blocks, size);
  //Check if cube lost
  if(size){
    if(blocks[0].m_x <= 130){//if detected object is left of center x
      motor.turnleft_Alignment();
    } else if(blocks[0].m_x >= 140){//if detected object i right of center x
      motor.turnright_Alignment();
    } else {
      mode = modes::GETCLOSERTOTHECUBE;
      return true;
    }
  } else {
    mode = modes::SEARCHING;
    return false;
  }
}
void GO_CLOSER() {
  pixy.pixy.ccc.getBlocks();
  if (pixy.pixy.ccc.numBlocks) {}
  int size = 0;
  auto value_m_y = pixy.GetBlocks(size)[0].m_y;
  while (value_m_y > 185) {
    motor.goback();
  }
  do {
    motor.gofront(SPEED_t::KLOW);
    auto blocks = pixy.GetBlocks(size);
    value_m_y = blocks[0].m_y;
  } while (value_m_y < 175 );
  motor.stop();
  mode = modes::PICKUP;
}

};

ModesClass controller;



void setup() {
  Serial.begin(115200);
  armController.setup(HAND_PIN, ARM_PIN);
  motor.setup();
  pixy.setup();
  mode = modes::SEARCHING;
}

void loop() {
  if (mode == modes::SEARCHING) {
    controller.Searching();
  }
  else if (mode == modes::GOTOTHECUBE) {
    controller.GOTHECUBE();
  } else if (mode == modes::GETCLOSERTOTHECUBE) {
    controller.GO_CLOSER();
  } else if (mode == modes::PICKUP) {
    armController.catchACube();
    mode = modes::SEARCHING;
  }
}