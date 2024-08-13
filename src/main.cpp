#include <Arduino.h>
#include <Pixy2.h>
#include <PIxy2CCC.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Ultrasonic.h>
#include "../lib/motorDriver.h"
#include "../lib/pixmeDriver.h"
#include "../lib/servoDriver.h"
#include "../lib/distanceSensor.h"
#include "../lib/pickupMotor.h"

#define DISTANCE 35
#define RIGHT_ECHO 28
#define RIGHT_TRIG 29
#define LEFT_ECHO 32
#define LEFT_TRIG 33

enum modes { 
  SEARCHING, 
  GOTOTHECUBE,
  PICKUP,
  ERROR
};

modes mode = modes::SEARCHING;
ServoMotorDriver servo;
PickupMotorDrive pickup;
MotorDriver motor;
Pixy2 pixy;

Ultrasonic left_sonic(RIGHT_TRIG, RIGHT_ECHO);
Ultrasonic right_sonic(LEFT_TRIG, LEFT_ECHO);

class Searching {
  public:
   static bool cubeIsFounded() {
      pixy.ccc.getBlocks();
      if(pixy.ccc.numBlocks){
        for (int i=0; i<pixy.ccc.numBlocks; i++) {
          if(pixy.ccc.blocks[i].m_signature==1 or pixy.ccc.blocks[i].m_signature==2){
            return true;
          };
        }
      }
      return false;
   }
  static void tryNotCrashWall() {
    int rightMiddle_distance = right_sonic.read();
    int leftMiddle_distance = left_sonic.read();
    Serial.print("right:");
    Serial.println(rightMiddle_distance);
    Serial.print("left:");
    Serial.println(leftMiddle_distance);
    Serial.println("---------------------------------------");
    if ((rightMiddle_distance > DISTANCE) && (leftMiddle_distance > DISTANCE)) {
      motor.gofront();
    } else if(rightMiddle_distance < leftMiddle_distance){
      motor.turnleft();
    } else{
      motor.turnright();
    }
  }
};


void GOTHECUBE_f(){
  Serial.println("--------------------------------------------");
  Serial.print("M_x");
  Serial.println(pixy.ccc.blocks[0].m_x);
  Serial.print("M_y");
  Serial.println(pixy.ccc.blocks[0].m_y);
  Serial.println("--------------------------------------------");
  Serial.println("--------------------------------------------");

  pixy.ccc.getBlocks();

  //Check if cube lost
  if(pixy.ccc.numBlocks){
    for (int i=0; i<pixy.ccc.numBlocks; i++){
      if(pixy.ccc.blocks[i].m_x < 154){//if detected object is left of center x
        motor.turnleft_Alignment();
      }
      else if(pixy.ccc.blocks[i].m_x > 164){//if detected object i right of center x
        motor.turnright_Alignment();
      }
      if (pixy.ccc.blocks[i].m_y < 120) {
        mode = modes::PICKUP;
      }
    }
  } else{
    mode = modes::SEARCHING;
  }
}

void PICKUP_f(){
  motor.stop();
  pickup.write(0);
  delay(300);
  servo.write(80);
  delay(300);
  //Grab the cube (CHANGE VALUE)
  pickup.write(180);
  delay(300);
  //Hands up
  servo.write(0);
  delay(300);
  mode = modes::SEARCHING;
}

float get_angle(float right_dimension, float left_dimension, float d = 11){
  float x = abs(right_dimension - left_dimension);
  return atan2(d,x) * 57.296;
}

void setup() {
  Serial.begin(115200);
  servo.setup(3);
  pickup.setup();
  motor.setup();
  pixy.init();
  pickup.write(180);
  servo.write(0);
}

bool moveAvibile = true;
void loop() {
  if (mode == modes::SEARCHING) {
    if(Searching::cubeIsFounded()) {
      mode = modes::GOTOTHECUBE;
    }
    Searching::tryNotCrashWall();
  }
  else if (mode == modes::GOTOTHECUBE) {
    GOTHECUBE_f();
  } else {
    PICKUP_f();
  }
  // Serial.print("Angle print: ");
  // Serial.println(get_angle(30,30));
}