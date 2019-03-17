#include <SPI.h>  
#include <Pixy.h>
#include "MeMegaPi.h"


// This is the main Pixy object 
Pixy pixy;
MeMegaPiDCMotor motor2(PORT1B); //Venstre
MeMegaPiDCMotor motor4(PORT2B); //Højre
int Vmotorspeed;
int Hmotorspeed;

unsigned long TurnCountLeft = 0;
unsigned long TurnCountRight = 0;


void setup()
{
  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();
}

void loop()
{ 
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32]; 
  // grab blocks!
  blocks = pixy.getBlocks();
  int LinePositionX = pixy.blocks[i].x - 120; //-160 er venstre, 160 er højre

  if (blocks && pixy.blocks[i].width > 250 && pixy.blocks[i].height > 15 && LinePositionX < 0){ //Drej til venstre
    Hmotorspeed = 0;
    Vmotorspeed = 255;
    motor2.run(-Hmotorspeed);
    motor4.run(Vmotorspeed);

    TurnCountLeft += 1;
    Serial.println(TurnCountLeft);
  } else if (blocks && pixy.blocks[i].width > 250 && pixy.blocks[i].height > 15 && LinePositionX > 0){ //Drej til højre
    Hmotorspeed = 255;
    Vmotorspeed = 0;
    motor2.run(-Hmotorspeed);
    motor4.run(Vmotorspeed);

    TurnCountRight += 1;
    //Serial.println(TurnCountRight);
   
  } else if (blocks && pixy.blocks[i].width > 5 && pixy.blocks[i].height > 15) //Følg linjen
  {
    Hmotorspeed = pow(1.03,-(LinePositionX))+0.6*-LinePositionX+170;
    Vmotorspeed = pow(1.03,LinePositionX)+0.6*LinePositionX+170;
    motor2.run(-Hmotorspeed);
    motor4.run(Vmotorspeed);
    //Serial.println(-Hmotorspeed);
    //Serial.println(Vmotorspeed);
  }  
}
