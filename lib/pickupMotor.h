#ifndef PICKUP_MOTOR_H_
#define PICKUP_MOTOR_H_

#include <Arduino.h>
#include <Servo.h>
class PickupMotorDrive {
  private:
   Servo motor;
  public:
   void setup(int pin, int start_position = 0) {
    motor.attach(pin);
    motor.write(start_position);
   }
   int write(int value) {
    motor.write(value);
   }
};

class ArmController {
 private:
  PickupMotorDrive arm;
  PickupMotorDrive claw;
 public:
  ArmController(): arm(), claw() {
  }
  void setup(int hand_pin, int arm_pin) {
    claw.setup(hand_pin, 0);
    arm.setup(arm_pin, 180);
  }
  void catchACube() {
    arm.write(0);
    claw.write(0);
    delay(700);
    claw.write(120);
    delay(1500);
  }
  void catchACube2() {
    arm.write(180);
    delay(1500);
    claw.write(0);
    delay(500);
  }
};


#endif  //  PICKUP_MOTOR_H_