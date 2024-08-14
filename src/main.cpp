#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include "../lib/new/pid_pixme.h"
#include "../lib/pixmeDriver.h"

PixyController pixy;
PIDPixmeController pid;
void setup() {
pixy.setup();
}

void loop() {
  if (pixy.CubeInView()) {
    pid.Dimension_update(pixy.Get_M_Y_Cube());
  }
}