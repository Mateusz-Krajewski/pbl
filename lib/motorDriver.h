#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include <Arduino.h>

#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define enA 8
#define enB 9

class MotorDriver {
 private:
  uint8_t speed = 125;
 public:
  void setup() {
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    pinMode(IN3,OUTPUT);
    pinMode(IN4,OUTPUT);
    analogWrite(enA, speed);
    analogWrite(enB, speed);
  }
  void gofront(){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
  };
  void stop() {
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
  }
  void turnright(){  
    analogWrite(enA,250);
    analogWrite(enB, 250);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    delay(200);
    analogWrite(enA, speed);
    analogWrite(enB, speed);
    this->stop();
    }
  void turnleft(){ 
    analogWrite(enA,250);
    analogWrite(enB, 250);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(200);
    analogWrite(enA, speed);
    analogWrite(enB, speed);
    this->stop();
    }
};

#endif  //  MOTOR_DRIVER_H_