#ifndef COMPASS_DRIVER_H_
#define COMPASS_DRIVER_H_
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Arduino.h>


class Compass {
 private:
  Adafruit_HMC5883_Unified sensor;

 public:
  Compass(): sensor() {}
  void setup() {
    sensor.begin();
  }
  float read() {
    sensors_event_t event;
    sensor.getEvent(&event);
    float heading = atan2(event.magnetic.y, event.magnetic.x);

  if(heading < 0) {
    heading += 2 * PI;
  }
  auto res = heading * 180/M_PI;
  Serial.print("Heading (degrees): ");
  Serial.println(res);
  return res;
  }
};

#endif  // COMPASS_DRIVER_H_