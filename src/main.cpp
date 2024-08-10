#include <Arduino.h>
#include <Servo.h>
#include <Pixy2.h>
#include <Pixy2CCC.h>
#include <Pixy2I2C.h>
#include <Pixy2Line.h>
#include <Pixy2SPI_SS.h>
#include <Pixy2UART.h>
#include <Pixy2Video.h>
#include <TPixy2.h>

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

class PixyController {
private:
  Pixy2 pixy;
public:
 void setup() {
  pixy.init();
 }
 Block* GetBlocks(int &size) {
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks) {
    size = pixy.ccc.numBlocks;
    return pixy.ccc.blocks;
  }
  return nullptr;
 }
};

ServoMotorDriver servo;
MotorDriver motor;
//PixyController pixy;

void setup() {
  Serial.begin(115200);
  servo.setup(11);
  motor.setup();
//  pixy.setup();
}

void loop() {
  motor.gofront();
  delay(1000);
  motor.turnright();
  delay(1000);
  // int size = 0;
  // auto blocks = pixy.GetBlocks(size);
  // if (size  > 0) {
  //   for (int i = 0; i < size; i++) {
  //     Serial.print("  block ");
  //     Serial.print(i);
  //     Serial.print(": ");
  //     //Serial.print(x);
  //     //Serial.println(y);
  //     blocks[i].print();
  //   }
  // }
}