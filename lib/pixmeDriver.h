#ifndef PIXME_DRIVER_H_
#define PIXME_DRIVER_H_

#include <Arduino.h>
#include <Pixy2.h>
#include <Pixy2CCC.h>
#include <Pixy2I2C.h>
#include <Pixy2Line.h>
#include <Pixy2SPI_SS.h>
#include <Pixy2UART.h>
#include <Pixy2Video.h>
#include <TPixy2.h>

class PixyController {
private:
  Pixy2 pixy;
public:
 void setup() {
  pixy.init();
 }
 bool CheckBlock(){
  pixy.ccc.getBlocks();
  if(pixy.ccc.numBlocks){
    return true;
  }
  else{
    return false;
  }
 }
 
 Block* GetBlocks(int &size) {
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks) {
    size = pixy.ccc.numBlocks;
    return pixy.ccc.blocks;
  }
  return nullptr;
 }
 int Get_M_X_Cube() {
  int size;
  auto blocks = this->GetBlocks(size);
  if (size > 0) {
    return blocks[0].m_x;
  }
 }
 int Get_M_Y_Cube() {
  int size;
  auto blocks = this->GetBlocks(size);
  if (size > 0) {
    return blocks[0].m_y;
  }
 }
 bool CubeInView() {
    int size;
    auto blocks = this->GetBlocks(size);
    if (size <= 0) {
        return false;
    }
    for (int i=0; i < size; i++) {
        if (blocks[i].m_signature == 1 || blocks[i].m_signature == 2) {
            return true;
        }
    }
    return false;
 }
};

#endif  //  PIXME_DRIVER_H_
