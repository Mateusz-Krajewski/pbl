#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include <Arduino.h>
#include "HMC5883L_Simple.h"

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
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
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
    delay(50);
    this->gofront();
    }
  void turnright(){ 
    analogWrite(enA,255);
    analogWrite(enB, 255);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(50);
    this->gofront();
    }
};


class SmartMotorDriver {
  private:
  HMC5883L_Simple compas;
  MotorDriver driver;
  public:
  SmartMotorDriver() :compas(), driver() {
  }
  void setup() {
    driver.setup();
  }
  void turn_right(float deg) {
    float start_value = compas.GetHeadingDegrees();
    Serial.print("Rotation Start Value:");
    Serial.println(start_value);
    while (compas.GetHeadingDegrees() < start_value + deg ) {
      driver.turnright();
      Serial.print("Rotation Value:");
      Serial.println(compas.GetHeadingDegrees());
    }
    Serial.println("--------------------------------------");
  }
  void turn_left(float deg) {
    float start_value = compas.GetHeadingDegrees();
    while (compas.GetHeadingDegrees() > start_value + deg ) {
      driver.turnright();
    }
  }
  void gofront() {
    driver.gofront();
  }
  void stop() {
    driver.stop();
  }
};

#endif  //  MOTOR_DRIVER_H_