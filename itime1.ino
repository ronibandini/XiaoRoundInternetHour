// Internet Time with XIAO Round TFT Display
// Roni Bandini, November 2023, @RoniBandini
// Xiao nrf52840 and TFT Round Display

#include <PNGdec.h>
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include "I2C_BM8563.h"
#include "NotoSansBold15.h"
#include "NotoSansBold36.h"
#include "charly.h" 
#include "itime.h" 

I2C_BM8563 rtc(I2C_BM8563_DEFAULT_ADDRESS, Wire);
I2C_BM8563_TimeTypeDef timeStruct;
I2C_BM8563_DateTypeDef dateStruct;

TFT_eSPI tft = TFT_eSPI();  
TFT_eSprite face = TFT_eSprite(&tft); 

// Edit with UTC+1 local time https://time.is/UTC+1 
uint8_t h = 13, m = 44, s = 40;

int refreshSeconds = 5000 ;

PNG png;  

#define MAX_IMAGE_WIDTH 240        

int16_t rc;

void setup()
{
  
  Serial.begin(115200);
    
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK); 

  Wire.begin();

  timeStruct.hours   = h;
  timeStruct.minutes = m;
  timeStruct.seconds = s;
  rtc.setTime(&timeStruct); 
  rtc.begin();     

  rc = png.openFLASH((uint8_t *)charly, sizeof(charly), pngDraw); 
  if (rc == PNG_SUCCESS) {    
    rc = png.decode(NULL, 0);   
    tft.startWrite();     
    tft.endWrite();   
  }

  Serial.println("\n\n Internet Time Beats Clock");   
  Serial.println("\n\n with XIAO Round TFT and nrf52840");   
  Serial.println("\n\n Roni Bandini, 11/2023");   
  Serial.println(""); 

  delay(5000);
 
}

void syncTime(void){  
  rtc.getTime(&timeStruct);
}

void loop()
{  

  float myBeats=(3600*timeStruct.hours+60*timeStruct.minutes+timeStruct.seconds)/86.4;    

  rc = png.openFLASH((uint8_t *)itime, sizeof(itime), pngDraw); 
  if (rc == PNG_SUCCESS) {    
    rc = png.decode(NULL, 0);   
    tft.startWrite();     
    tft.endWrite();   
  }

  tft.loadFont(NotoSansBold36);
  tft.drawString("@"+String(myBeats), 40, 100);    
  
  tft.loadFont(NotoSansBold15);
  String myMinutes=String(timeStruct.minutes);
  if (myMinutes.length()<2) {myMinutes="0"+myMinutes;}
  tft.drawString(String(timeStruct.hours)+":"+myMinutes, 100, 195);
  
  Serial.println("@"+String(myBeats)+".beats");
  Serial.println("Hour: ");
  Serial.println(timeStruct.hours );
  Serial.println("Minutes: ");
  Serial.println(timeStruct.minutes);
  Serial.println("Seconds: ");
  Serial.println(timeStruct.seconds);

  delay(refreshSeconds);
  syncTime();
  
  tft.fillScreen(TFT_BLACK);

}

void pngDraw(PNGDRAW *pDraw) {
  uint16_t lineBuffer[MAX_IMAGE_WIDTH];
  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  tft.pushImage(0, 0 + pDraw->y, pDraw->iWidth, 1, lineBuffer);
}
