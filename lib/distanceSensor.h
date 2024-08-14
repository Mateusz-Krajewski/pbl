#ifndef DISTANCE_SENSOR_H_
#define DISTANCE_SENSOR_H_
#include <Arduino.h>
#include <Ultrasonic.h>

class DistanceSensor {
 private:
  Ultrasonic sensor;
 public:
  DistanceSensor(int trig, int echo): sensor(trig, echo) {
  }
  uint32_t read() {
    return sensor.read();
  }
};

#endif  // DISTANCE_SENSOR_H_