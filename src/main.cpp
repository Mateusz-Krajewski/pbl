#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Ultrasonic.h>
#include "../lib/motorDriver.h"
#include "../lib/pixmeDriver.h"
#include "../lib/servoDriver.h"
#include "../lib/distanceSensor.h"
#include "../lib/pickupMotor.h"

#define DISTANCE 25

#define RIGHT_ECHO 28
#define RIGHT_TRIG 29
#define LEFT_ECHO 4
#define LEFT_TRIG 5
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
//PixyController pixy;

Ultrasonic left_sonic(RIGHT_TRIG, RIGHT_ECHO);
Ultrasonic right_sonic(LEFT_TRIG, LEFT_ECHO);

void SEARCHING_f(){
  //MOVING
  int rightMiddle_distance = right_sonic.read();
  int leftMiddle_distance = left_sonic.read();
  Serial.print("right:");
  Serial.println(rightMiddle_distance);
  Serial.print("left:");
  Serial.println(leftMiddle_distance);
  if ((rightMiddle_distance > DISTANCE) && (leftMiddle_distance > DISTANCE)) {
    motor.gofront();
  } 
  else if(rightMiddle_distance < leftMiddle_distance){
    motor.turnleft();
  }
  else{
    motor.turnright();
  }

  //LOOKING
  //if(pixy.found()){
  //  mode == modes::GOTOTHECUBE;
  //}
}

void GOTHECUBE_f(){
  //Hand down
  servo.write(0);
}

void PICKUP_f(){
  //Grab the cube (CHANGE VALUE)
  pickup.write(0);
  delay(100);
  //Hands up
  servo.write(180);

  //Drop the cube (CHANGE VALUE)
  pickup.write(10);
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
  //pixy.setup();
}

bool moveAvibile = true;
void loop() {
  if (mode == modes::SEARCHING) {
    SEARCHING_f();
  }
  else if (mode == modes::GOTOTHECUBE) {
    GOTHECUBE_f();
  } else {
    PICKUP_f();
  }
  // Serial.print("Angle print: ");
  // Serial.println(get_angle(30,30));
  // motor.stop();
  // int rightMiddle_distance = right_sonic.read();
  // int leftMiddle_distance = left_sonic.read();
  // Serial.print("Right: ");
  // Serial.println(rightMiddle_distance);
  // Serial.print("Left: ");
  // Serial.println(leftMiddle_distance);
  // Serial.println();
  // Serial.println();
  // Serial.println();
  // if ((rightMiddle_distance > DISTANCE) && (leftMiddle_distance > DISTANCE)) {
  //   motor.gofront();
  // } 
  // else if(rightMiddle_distance < leftMiddle_distance){
  //   motor.turnleft();
  // }
  // else{
  //   motor.turnright();
  // }
  // delay(100);
}