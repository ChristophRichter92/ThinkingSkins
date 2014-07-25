#include <Servo.h>
#include "tsServoDriver.h"

// LED STUFF
// Library: https://github.com/adafruit/Adafruit_NeoPixel
// Tutorial: https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library

#include <Adafruit_NeoPixel.h>

#define LEDPIN 11
 
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_KHZ800 800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
// NEO_KHZ400 400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
// NEO_GRB Pixels are wired for GRB bitstream (most NeoPixel products)
// NEO_RGB Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(9, LEDPIN, NEO_GRB + NEO_KHZ800);

Servo servoVert;
Servo servoHori;

int VERT_MIN = 70;
int HORI_MIN = 85;
int VERT_MID = 75;
int HORI_MID = 130;
int VERT_MAX = 125;
int HORI_MAX = 180;

// global offset variable
Coord offset(HORI_MID, VERT_MID);
int up = 1;
int left = 1;

void setup() 
{ 
  servoVert.attach(9);  // attaches the servo on pin 9 to the servo object
  servoHori.attach(10);  // attaches the servo on pin 10 to the servo object
  
  // LED setup
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
} 

void loop() 
{ 
  // LED stuff
  uint32_t red = strip.Color(255, 0, 0);
  uint32_t blue = strip.Color(0, 0, 255);
  uint32_t green = strip.Color(0, 255, 0);
  uint32_t white = strip.Color(255, 255, 255);
  strip.setPixelColor(0, white);
  strip.setPixelColor(1, white);
  strip.setPixelColor(2, white);
  strip.setPixelColor(3, white);
  strip.setPixelColor(4, white);
  strip.setPixelColor(5, white);
  strip.setPixelColor(6, white);
  strip.setPixelColor(7, white);
  strip.setPixelColor(8, white);
  strip.setBrightness(255);
  strip.show();
  
  /*
  // This moves the plate from open to closed in every cycle.
  if (up == 1){
    up = 0;
    offset.setTo(HORI_MAX, VERT_MID);
  } else {
    up = 1;
    offset.setTo(HORI_MID, VERT_MID);
  }
  */
  ///*
  // This moves the plate like an old windows screensaver.
  if(offset.getY() >= VERT_MAX) up = 0;
  if(offset.getX() >= HORI_MAX) left = 0;
  if(offset.getY() <= VERT_MIN) up = 1;
  if(offset.getX() <= HORI_MIN) left = 1;
  
  if(up == 1){
    offset.incY();
  } else offset.decY();
  
  if(left == 1){
    offset.incX();
  } else offset.decX();
  //*/
  // do this every loop
  setServos(offset);
  delay(20);
}

void setServos(Coord newPos)
{
  servoVert.write(newPos.getY());
  servoHori.write(newPos.getX());
}

