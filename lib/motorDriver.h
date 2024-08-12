#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include <Arduino.h>

#define IN1 22
#define IN2 23
#define IN3 24
#define IN4 25
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
    analogWrite(enA, speed);
    analogWrite(enB, speed);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(25);
  };
  void stop() {
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
  }
  void turnleft(){  
    analogWrite(enA,255);
    analogWrite(enB, 255);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    delay(550);
    this->gofront();
    }
  void turnright(){ 
    analogWrite(enA,255);
    analogWrite(enB, 255);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(550);
    this->gofront();
    }
};

#endif  //  MOTOR_DRIVER_H_