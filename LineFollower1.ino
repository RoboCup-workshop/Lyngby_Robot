//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This sketch is a good place to start if you're just getting started with 
// Pixy and Arduino.  This program simply prints the detected object blocks 
// (including color codes) through the serial console.  It uses the Arduino's 
// ICSP port.  For more information go here:
//
// http://cmucam.org/projects/cmucam5/wiki/Hooking_up_Pixy_to_a_Microcontroller_(like_an_Arduino)
//
// It prints the detected blocks once per second because printing all of the 
// blocks for all 50 frames per second would overwhelm the Arduino's serial port.
//
   
#include <SPI.h>  
#include <Pixy.h>
#include "MeMegaPi.h"

// This is the main Pixy object 
Pixy pixy;

MeMegaPiDCMotor motor1(PORT1A);
MeMegaPiDCMotor motor2(PORT1B); //Venstre
MeMegaPiDCMotor motor4(PORT2B); //Højre
MeMegaPiDCMotor motor3(PORT2A);

int Vmotorspeed;
int Hmotorspeed;

unsigned long TurnCount = 0;

void setup()
{
  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();
}

void loop() {
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32]; 
  // grab blocks!
  blocks = pixy.getBlocks();
  

  if (blocks && pixy.blocks[i].width > 200 && pixy.blocks[i].height > 15) {
    
    Hmotorspeed = 0;
    Vmotorspeed = 255;
    
    motor2.run(-Hmotorspeed);
    motor4.run(Vmotorspeed);

    TurnCount += 1;
    Serial.println(TurnCount);
   
    } else if(blocks && pixy.blocks[i].width > 5 && pixy.blocks[i].height > 15) {
        
        int LinePositionX = pixy.blocks[i].x - 160;
        
        Hmotorspeed = pow(1.03,-(LinePositionX))+0.2*-LinePositionX+100;
        Vmotorspeed = pow(1.03,LinePositionX)+0.2*LinePositionX+100;
        
        motor2.run(-Hmotorspeed);
        motor4.run(Vmotorspeed);
        
        //Serial.println(-Hmotorspeed);
        //Serial.println(Vmotorspeed);
     }  
}
