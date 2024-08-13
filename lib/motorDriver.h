#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include <Arduino.h>
#include "compassDriver.h"

#define IN1 22
#define IN2 23
#define IN3 24
#define IN4 25
#define enA 8
#define enB 9

namespace {
  constexpr auto DEFAULT_SPEED = 100;
  constexpr auto TURN_SPEED = 255;
  constexpr auto INCORECT_OF_COMPASS = 0.05;

  constexpr auto LOW_TURN_SPPED = 120;
  constexpr auto LOW_TURN_TIME = 10;
}

class MotorDriver {
 private:
  uint8_t speed = DEFAULT_SPEED;
 public:
  void stop() {
    analogWrite(enA, 0);
    analogWrite(enB, 0);
  }
  void setup() {
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    pinMode(IN3,OUTPUT);
    pinMode(IN4,OUTPUT);
    analogWrite(enA, speed);
    analogWrite(enB, speed);
  }
  void goback(){
    analogWrite(enA, speed);
    analogWrite(enB, speed);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(25);
  };
  void gofront(){
    analogWrite(enA, speed);
    analogWrite(enB, speed);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    delay(25);
    
  }
  void turnleft(){  
    Serial.println("turning left");
    analogWrite(enA,TURN_SPEED);
    analogWrite(enB, TURN_SPEED);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    delay(350);
    stop();
    }
  void turnright(){ 
    Serial.println("turning right");
    analogWrite(enA,TURN_SPEED);
    analogWrite(enB, TURN_SPEED);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(350);
    }
  void turnleft_Alignment(){  
    Serial.println("turning left");
    analogWrite(enA,LOW_TURN_SPPED);
    analogWrite(enB, LOW_TURN_SPPED);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    delay(LOW_TURN_TIME);
  }
  void turnright_Alignment(){ 
    Serial.println("turning right");
    analogWrite(enA,LOW_TURN_SPPED);
    analogWrite(enB, LOW_TURN_SPPED);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(LOW_TURN_TIME);
  }
};

// w prawo zwiekszanie
class SmartMotorDriver {
 private:
  Compass compas;
  void changespeed(int speed) {
    analogWrite(enA, speed);
    analogWrite(enB, speed);
  }
  void turnleft(){  
    Serial.println("turning left");
    changespeed(255);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    delay(25);
    changespeed(DEFAULT_SPEED);
    }
  void turnright(){ 
    Serial.println("turning right");
    changespeed(TURN_SPEED);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(15);
    }
 public:
  SmartMotorDriver(): compas() {}
  void gofront(int time_ms = 150){
    changespeed(DEFAULT_SPEED);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    delay(time_ms);
  }
  void stop() {
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
  }
  void setup() {
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    pinMode(IN3,OUTPUT);
    pinMode(IN4,OUTPUT);
    changespeed(DEFAULT_SPEED);
    compas.setup();
  }
  void turnRight(float angle) {
    auto start_val = compas.read();
    auto end_val = start_val + angle;
    Serial.print("startValue: ");
    Serial.println(start_val);
    if (start_val + angle < 360) {
      while (!(compas.read() < end_val*(1+INCORECT_OF_COMPASS) && compas.read() > end_val*(1-INCORECT_OF_COMPASS))) {
        if (compas.read() < end_val*(1+INCORECT_OF_COMPASS)) {
          turnright();
        } else if (compas.read() > end_val*(1-INCORECT_OF_COMPASS)) {
          turnleft();
        }
        Serial.print("stil turning:");
        Serial.println(compas.read());
      } 
    } else {
      while (compas.read() + 360 < end_val*(1+INCORECT_OF_COMPASS) && compas.read() + 360 > end_val*(1-INCORECT_OF_COMPASS)) {
        if (compas.read() + 360 < end_val*(1+INCORECT_OF_COMPASS)) {
          turnright();
        } else if (compas.read() + 360 > end_val*(1-INCORECT_OF_COMPASS)) {
          turnleft();
        }
        Serial.print("stil turning:");
        Serial.println(compas.read());
      } 
    }
  }
    void turnLeft(float angle) {
    auto start_val = compas.read();
    auto end_val = start_val - angle;
    Serial.print("startValue: ");
    Serial.println(start_val);
    if (end_val > 0) {
      while (!(compas.read() < end_val*(1+INCORECT_OF_COMPASS) && compas.read() > end_val*(1-INCORECT_OF_COMPASS))) {
        Serial.print("stil turning:");
        Serial.println(compas.read());
        this->turnright();
      } 
    } else {

    }
  }
};

#endif  //  MOTOR_DRIVER_H_