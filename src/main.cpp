#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "../lib/motorDriver.h"
#include "../lib/pixmeDriver.h"
#include "../lib/servoDriver.h"

ServoMotorDriver servo;
MotorDriver motor;
//PixyController pixy;

void setup() {
  Serial.begin(115200);
  servo.setup(11);
  motor.setup();
//  pixy.setup();
}

void loop() {
  motor.gofront();
  delay(1000);
  motor.turnright();
  delay(1000);
  // int size = 0;
  // auto blocks = pixy.GetBlocks(size);
  // if (size  > 0) {
  //   for (int i = 0; i < size; i++) {
  //     Serial.print("  block ");
  //     Serial.print(i);
  //     Serial.print(": ");
  //     //Serial.print(x);
  //     //Serial.println(y);
  //     blocks[i].print();
  //   }
  // }
}