#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include <Arduino.h>

namespace {
  constexpr auto IN1 = 22;
  constexpr auto IN2 = 23;
  constexpr auto IN3 = 24;
  constexpr auto IN4 = 25;
  constexpr auto enA = 8;
  constexpr auto enB = 9;
}

namespace {
  constexpr auto DEFAULT_LOW_SPEED = 110;
  constexpr auto DEFAULT_MIDLE_SPEED = 120;
  constexpr auto DEFAULT_HIGH_SPEED = 170;
  constexpr auto TURN_SPEED = 255;
  // constexpr auto INCORECT_OF_COMPASS = 0.05;

  constexpr auto LOW_TURN_SPPED = 175;
  constexpr auto LOW_TURN_TIME = 50;
}


enum SPEED_t : uint8_t {
  KLOW = DEFAULT_LOW_SPEED,
  KMIDLE = DEFAULT_MIDLE_SPEED,
  KHIGH = DEFAULT_HIGH_SPEED,
  KTURN = TURN_SPEED,
  KLOWTURN = LOW_TURN_SPPED,
};

class MotorDriver {
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
    analogWrite(enA, SPEED_t::KMIDLE);
    analogWrite(enB, SPEED_t::KMIDLE);
  }
  void goback(int d_time =200){
    analogWrite(enA, SPEED_t::KHIGH);
    analogWrite(enB, SPEED_t::KHIGH);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(d_time);
    stop();
  };
  void gofront(SPEED_t speed = SPEED_t::KMIDLE){
    analogWrite(enA, speed);
    analogWrite(enB, speed);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    delay(50);
    stop();
  }
  void turnleft(SPEED_t speed = SPEED_t::KTURN){  
    Serial.println("turning left");
    analogWrite(enA, speed);
    analogWrite(enB, speed);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    delay(350);
    stop();
    }
  void turnright(SPEED_t speed = SPEED_t::KTURN){ 
    Serial.println("turning right");
    analogWrite(enA, speed);
    analogWrite(enB, speed);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(350);
    stop();
    }
  void turnleft_Alignment(SPEED_t speed = SPEED_t::KLOWTURN) {  
    Serial.println("turning left");
    analogWrite(enA, speed);
    analogWrite(enB, speed);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    delay(LOW_TURN_TIME);
    stop();
  }
  void turnright_Alignment(SPEED_t speed = SPEED_t::KLOWTURN) { 
    Serial.println("turning right");
    analogWrite(enA, speed);
    analogWrite(enB, speed);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(LOW_TURN_TIME);
    stop();
  }
};

// w prawo zwiekszanie
// class SmartMotorDriver {
//  private:
//   Compass compas;
//   void changespeed(int speed) {
//     analogWrite(enA, speed);
//     analogWrite(enB, speed);
//   }
//   void turnleft(){  
//     Serial.println("turning left");
//     changespeed(255);
//     digitalWrite(IN1,HIGH);
//     digitalWrite(IN2,LOW);
//     digitalWrite(IN3,LOW);
//     digitalWrite(IN4,HIGH);
//     delay(25);
//     changespeed(DEFAULT_SPEED);
//     }
//   void turnright(){ 
//     Serial.println("turning right");
//     changespeed(TURN_SPEED);
//     digitalWrite(IN1,LOW);
//     digitalWrite(IN2,HIGH);
//     digitalWrite(IN3,HIGH);
//     digitalWrite(IN4,LOW);
//     delay(15);
//     }
//  public:
//   SmartMotorDriver(): compas() {}
//   void gofront(int time_ms = 150){
//     changespeed(DEFAULT_SPEED);
//     digitalWrite(IN1,LOW);
//     digitalWrite(IN2,HIGH);
//     digitalWrite(IN3,LOW);
//     digitalWrite(IN4,HIGH);
//     delay(time_ms);
//   }
//   void stop() {
//     digitalWrite(IN1,LOW);
//     digitalWrite(IN2,LOW);
//     digitalWrite(IN3,LOW);
//     digitalWrite(IN4,LOW);
//   }
//   void setup() {
//     pinMode(IN1,OUTPUT);
//     pinMode(IN2,OUTPUT);
//     pinMode(IN3,OUTPUT);
//     pinMode(IN4,OUTPUT);
//     changespeed(DEFAULT_SPEED);
//     compas.setup();
//   }
//   void turnRight(float angle) {
//     auto start_val = compas.read();
//     auto end_val = start_val + angle;
//     Serial.print("startValue: ");
//     Serial.println(start_val);
//     if (start_val + angle < 360) {
//       while (!(compas.read() < end_val*(1+INCORECT_OF_COMPASS) && compas.read() > end_val*(1-INCORECT_OF_COMPASS))) {
//         if (compas.read() < end_val*(1+INCORECT_OF_COMPASS)) {
//           turnright();
//         } else if (compas.read() > end_val*(1-INCORECT_OF_COMPASS)) {
//           turnleft();
//         }
//         Serial.print("stil turning:");
//         Serial.println(compas.read());
//       } 
//     } else {
//       while (compas.read() + 360 < end_val*(1+INCORECT_OF_COMPASS) && compas.read() + 360 > end_val*(1-INCORECT_OF_COMPASS)) {
//         if (compas.read() + 360 < end_val*(1+INCORECT_OF_COMPASS)) {
//           turnright();
//         } else if (compas.read() + 360 > end_val*(1-INCORECT_OF_COMPASS)) {
//           turnleft();
//         }
//         Serial.print("stil turning:");
//         Serial.println(compas.read());
//       } 
//     }
//   }
//     void turnLeft(float angle) {
//     auto start_val = compas.read();
//     auto end_val = start_val - angle;
//     Serial.print("startValue: ");
//     Serial.println(start_val);
//     if (end_val > 0) {
//       while (!(compas.read() < end_val*(1+INCORECT_OF_COMPASS) && compas.read() > end_val*(1-INCORECT_OF_COMPASS))) {
//         Serial.print("stil turning:");
//         Serial.println(compas.read());
//         this->turnright();
//       } 
//     } else {

//     }
//   }
// };

#endif  //  MOTOR_DRIVER_H_