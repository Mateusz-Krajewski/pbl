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
public:
  Pixy2 pixy;
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
  do{
    pixy.ccc.getBlocks();
  } while (!pixy.ccc.numBlocks);
    return pixy.ccc.blocks;
 }
 bool CubeInView() {
    int size;
    pixy.ccc.getBlocks();
    if (pixy.ccc.numBlocks <= 0) {
        return false;
    }
    for (int i=0; i < size; i++) {
        if (pixy.ccc.blocks[i].m_signature == 1 || pixy.ccc.blocks[i].m_signature == 2) {
            return true;
        }
    }
    return false;
 }
};

#endif  //  PIXME_DRIVER_H_
