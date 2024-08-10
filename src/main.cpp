#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Ultrasonic.h>
#include "../lib/motorDriver.h"
#include "../lib/pixmeDriver.h"
#include "../lib/servoDriver.h"
#include "../lib/distanceSensor.h"

#define DISTANCE 20

#define RIGHT_ECHO 2
#define RIGHT_TRIG 3
#define LEFT_ECHO 4
#define LEFT_TRIG 5



ServoMotorDriver servo;
MotorDriver motor;
//PixyController pixy;
Ultrasonic front_sonic(29, 28);
Ultrasonic left_sonic(RIGHT_TRIG, RIGHT_ECHO);
Ultrasonic right_sonic(LEFT_TRIG, LEFT_ECHO);



void setup() {
  Serial.begin(115200);
  servo.setup(11);
  motor.setup();
  motor.gofront();
//  pixy.setup();
}

bool moveAvibile = true;
void loop() {
  motor.stop();
  int right_distance = right_sonic.read();
  int left_distance = left_sonic.read();
  int front_distance = front_sonic.read();

  if ((front_distance > DISTANCE)) {
    motor.gofront();
  } else {
    motor.turnright();
  }
  delay(50);
}