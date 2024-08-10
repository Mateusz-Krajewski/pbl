#ifndef SERVO_DRIVER_H_
#define SERVO_DRIVER_H_

#include <Arduino.h>
#include <Servo.h>

class ServoMotorDriver {
  private:
   Servo motor;
  public:
   void setup(int pin) {
    motor.attach(pin);
   }
   int write(int value) {
    motor.write(value);
   }
};
#endif  //  SERVO_DRIVER_H_