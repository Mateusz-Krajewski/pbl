#ifndef PICKUP_MOTOR_H_
#define PICKUP_MOTOR_H_

#include <Arduino.h>
#include <Servo.h>
#define PIN 4
class PickupMotorDrive {
  private:
   Servo motor;
  public:
   void setup(int start_position = 0) {
    motor.attach(PIN);
    motor.write(start_position);
   }
   int write(int value) {
    motor.write(value);
    delay(10);
   }
};

#endif  //  PICKUP_MOTOR_H_