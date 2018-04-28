#include <Pixy.h>
#include <SPI.h>  

Pixy pixy;
uint16_t AverageArea; 
uint16_t CountAverage; 
uint16_t CountThisRound; 
uint32_t TotalArea;
uint16_t AverageThisRound;
uint16_t TotalThisRound;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pixy.init();   
}

void loop() {
  uint16_t blocks;
  char buf[32];
  static int i = 0;
  int j = 0;
  static int k = 0;
  blocks = pixy.getBlocks();
  for (j=0; j<blocks; j++){
    CountAverage += 1;
    TotalArea = TotalArea + pixy.blocks[j].width * pixy.blocks[j].height;
    AverageArea = TotalArea/CountAverage;

    CountThisRound += 1;
    TotalThisRound = TotalThisRound + pixy.blocks[j].width * pixy.blocks[j].height;
    AverageThisRound = TotalThisRound/CountThisRound;
        
    }
    if (AverageThisRound < AverageArea * 0.5 && AverageThisRound > 0){
      Serial.println("===========================Der er en bil.===============================");
  }
    if (AverageThisRound > 0){
      
    }
    if (AverageArea < 70){
      AverageArea = 71;
  }
  k++;
  if(k%100==0){
  
  Serial.print(" ATR ");
  Serial.print(AverageThisRound);
  Serial.print(" AA ");
  Serial.print(AverageArea);  
  Serial.print(" K ");
  Serial.println(k);

  
  
  AverageThisRound = 0;
  TotalThisRound = 0;
  CountThisRound = 0;
   
  }

}
