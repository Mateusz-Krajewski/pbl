#ifndef PICKUP_MOTOR_H_
#define PICKUP_MOTOR_H_

#include <Arduino.h>
#include <Servo.h>
#define PIN 4
class PickupMotorDrive {
  private:
   Servo motor;
  public:
   void setup() {
    motor.attach(PIN);
   }
   int write(int value) {
    motor.write(value);
    delay(10);
   }
};

#endif  //  PICKUP_MOTOR_H_