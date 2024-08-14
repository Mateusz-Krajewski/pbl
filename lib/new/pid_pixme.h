#include <PID_v1.h>
#include <Arduino.h>

namespace {
    constexpr double kp = 2.05;
    constexpr double ki = 0.08;
    constexpr double kd = 0.001;
} // namespace

namespace {
    constexpr double kp2 = 2.05;
    constexpr double ki2 = 0.08;
    constexpr double kd2 = 0.001;
} // namespace

namespace {
  constexpr auto IN1 = 22;
  constexpr auto IN2 = 23;
  constexpr auto IN3 = 24;
  constexpr auto IN4 = 25;
  constexpr auto enA = 8;
  constexpr auto enB = 9;
}

class MotorDriverForPID {
 private:
  
 public:
    void setup() {
        pinMode(IN1,OUTPUT);
        pinMode(IN2,OUTPUT);
        pinMode(IN3,OUTPUT);
        pinMode(IN4,OUTPUT);
        pinMode(enA, OUTPUT);
        pinMode(enB, OUTPUT);
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
    }
    void changeSpeed(int right_speed, int left_speed) {
        if (right_speed >=0) {
            digitalWrite(IN1,LOW);
            digitalWrite(IN2,HIGH);
        } else {
            digitalWrite(IN1,HIGH);
            digitalWrite(IN2,LOW);
        }
        if (right_speed >=0) {
            digitalWrite(IN3,LOW);
            digitalWrite(IN4,HIGH);
        } else {
            digitalWrite(IN3,HIGH);
            digitalWrite(IN4,LOW);
        }
        analogWrite(enA, right_speed);
        analogWrite(enB, left_speed);
    }
};


class PIDPixmeController {
 private:
  PID pid;
  PID pid_2;
  MotorDriverForPID driver;
  double Input;
  double Output;
  double setpoint;
  double Input2;
  double Output2;
  double setpoint2;
 public:
 PIDPixmeController():pid(&Input, &Output, &setpoint, kp, ki, kd, DIRECT), pid_2(&Input2, &Output2, &setpoint2, kp2, ki2, kd2, DIRECT) {
    driver.setup();
    setpoint = 135;
    setpoint2 = 180;
    pid.SetMode(AUTOMATIC);
    pid_2.SetMode(AUTOMATIC);
    pid.SetOutputLimits(-255, 255);
    pid.SetOutputLimits(-255, 255);
 }
 void Center_update(uint32_t position_x) {
    Input = position_x;
    pid.Compute();
    if (Output > 0) {
        auto fix_output = constrain(Output, 0, 255);
        driver.changeSpeed(0, fix_output);

    } else if (Output < 0) {
        auto fix_output = constrain(-Output, 30, 255);
        driver.changeSpeed(fix_output, 0);
    } else {
        driver.changeSpeed(0, 0);
    }
 }
 void Dimension_update(uint32_t position_y) {
    Input2 = position_y;
    pid_2.Compute();
    driver.changeSpeed(Output2, Output2);
 }
};
