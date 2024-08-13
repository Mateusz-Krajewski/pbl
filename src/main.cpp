#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Ultrasonic.h>
#include "../lib/motorDriver.h"
#include "../lib/pixmeDriver.h"
#include "../lib/servoDriver.h"
#include "../lib/distanceSensor.h"
#include "../lib/pickupMotor.h"

SmartMotorDriver driver;
void setup() {
  driver.setup();
  Serial.begin(115200);
}

void loop() {
  driver.turn_right(90);
  delay(5000);
}