#include <Arduino.h>
#include <Ultrasonic.h>

class SonicDriver {
 private:
  Ultrasonic sensor;
 public:
  SonicDriver(uint8_t echo, uint8_t trig): sensor(trig, echo) {}
  unsigned int read() {
    return sensor.read();
  }
};