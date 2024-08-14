#include <PID_v1.h>
#include <Arduino.h>
#include "compassDriver.h"

class MotorDriver {
 public:
  void setup() {

  }
  void stop() {

  }
  void start() {

  }
  void change_speed(int left, int right) {

  }
};


class PIDController {
 private:
  double Setpoint, Input, Output;
  double Kp = 2.0, Ki = 5.0, Kd = 1.0;
  PID pid;

  MotorDriver driver;
  Compass compass;
 public:
  PIDController(): pid(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT),
                    compass(), driver() {
  }
  void setup() {
    Setpoint = 90.0;
    pid.SetMode(AUTOMATIC);
  }
  void loop() {
    Input = compass.read();
    pid.Compute();
    int base_speed = 100;
    int left_speed = base_speed + Output;
    int right_speed = base_speed - Output;
    left_speed = constrain(left_speed, 0, 255);
    right_speed = constrain(right_speed, 0, 255);
    driver.change_speed(left_speed, right_speed);
    Serial.print("right speed:");
    Serial.println(right_speed);
    Serial.print("lrft speed:");
    Serial.println(left_speed);
  }
};

