#include "MeMCore.h"
#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;

MeDCMotor motor3(M1); //Left
MeDCMotor motor4(M2); //Right
int signature = 0;
int x = 0;                      //positon x axis
int y = 0;                      //position y axis
unsigned int width = 0;         //object's width
unsigned int height = 0;        //object's height
unsigned int area = 0;
unsigned int newarea = 0;
int Xmin = 70;                  //min x position
int Xmax = 200;                 //max x position
int maxArea = 0;
int minArea = 0;
int Speed = 70;                 //speed for motor
static int i = 0;

void setup()
{ 
  Serial.begin(9600);
  Stop();
  pixy.init();
}

void loop()
{ 
  while(millis()<5000)
  {
    scan();
    area = width * height; //calculate the object area 
    maxArea = area + 1000;
    minArea = area - 1000;
  }

    scan(); 

  if(signature == 2)//looking for signature 2
  {
    newarea = width * height; //calculate the object area
    
      if (x < Xmin)//turn left if x position < max x position
      {     
       left();
      }
      else if (x > Xmax) //turn right if x position > max x position
      {
       right();
      }
      else if(newarea < minArea)//go forward if object too small
      {
       forward(); 
      }
      else if(newarea > maxArea)//go backward if object too big
      {
       backward(); 
      }
      
      //else stop
      else
      {
        Stop(); 
      } 
   }
   else
   {
    Stop();
     }
}

void backward()//backward
  {
  motor3.run(Speed);
  motor4.run(-Speed);
  }

void forward()//forward
  {
  motor3.run(-Speed);
  motor4.run(Speed);
  }

void right()//turn right
  {
  motor3.run(-Speed);
  motor4.stop();
  }

void left()//turn left
  {
  motor3.stop();
  motor4.run(Speed);
  }

void Stop()//stop
  {
  motor3.stop();
  motor4.stop();
  }
  
void scan()
  {
  uint16_t blocks;
  blocks = pixy.getBlocks();  //receive data from pixy 
  signature = pixy.blocks[i].signature;    //get object's signature
  x = pixy.blocks[i].x;                    //get x position
  y = pixy.blocks[i].y;                    //get y position
  width = pixy.blocks[i].width;            //get width
  height = pixy.blocks[i].height;          //get height
  }  
