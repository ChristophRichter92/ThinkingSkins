#include <Servo.h>
#include "tsServoDriver.h"

// LED STUFF
// Library: https://github.com/adafruit/Adafruit_NeoPixel
// Tutorial: https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library

#include <Adafruit_NeoPixel.h>

#define LEDPIN 11

// Servo calibration
#define VERT_MIN 70
#define HORI_MIN 85
#define VERT_MID 75
#define HORI_MID 130
#define VERT_MAX 125
#define HORI_MAX 180

#define OPENX
#define OPENY
// calculation of the vertical and horizontal ranges
#define VERT_RANGE (VERT_MAX - VERT_MIN)
#define HORI_RANGE (HORI_MAX - HORI_MIN)

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

// serial communication setup variables for calibration
String strSerialInput = "";
boolean inputComplete = false;

// global offset variable
Coord offset(80, 0);
int up = 1;
int left = 1;

void setup() 
{ 
  Serial.begin(9600);
  
  servoVert.attach(9);  // attaches the servo on pin 9 to the servo object
  servoHori.attach(10);  // attaches the servo on pin 10 to the servo object
  
  // LED setup
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
} 

void loop() 
{ 
  // LED stuff
  /*
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
  */
  /*
  // This moves the plate from open to closed in every cycle.
  if (up == 1){
    up = 0;
    offset.setTo(0, 0);
  } else {
    up = 1;
    offset.setTo(255, 0);
  }
  */
  /*
  // This moves the plate like an old windows screensaver.
  if(offset.getY() >= 255) up = 0;
  if(offset.getX() >= 255) left = 0;
  if(offset.getY() <= 0) up = 1;
  if(offset.getX() <= 0) left = 1;
  
  if(up == 1){
    offset.incY();
  } else offset.decY();
  
  if(left == 1){
    offset.incX();
  } else offset.decX();
  */
  
  // Calibration program, calibrate via serial input
  ///*
  if (inputComplete) {
    String xInp = getValue(strSerialInput, ',', 0);
    String yInp = getValue(strSerialInput, ',', 1);
    offset.setX( xInp.toInt() );
    offset.setY( yInp.toInt() );
    Serial.println("got it");
    Serial.println(strSerialInput);
    strSerialInput = "";
    inputComplete = false;
    setServosAbsolute(offset);
  }
  //*/
  // do this every loop  
  // setServos(offset);
  delay(5);
}

/**
 * Sets the servos to a given coodinate within the range from (0,0) to (255, 255).
 */
void setServos(Coord newPos)
{
  //Serial.println(newPos.getX());
  //Serial.println(newPos.getX()/255);
  Serial.println(round(( (float)newPos.getX()/255 ) * HORI_RANGE));
  int xOfRange = round(( (float)newPos.getX()/255 ) * HORI_RANGE);
  int yOfRange = round(( (float)newPos.getY()/255 ) * VERT_RANGE);
  setServosAbsolute(HORI_MIN + xOfRange, VERT_MIN + yOfRange);
}

/**
 * Sets the servos to a true value (between 0 and 180) even though that might
 * might be out of range for the actual setup.
 * @private
 */
void setServosAbsolute(Coord newPos)
{
  servoVert.write(newPos.getY());
  servoHori.write(newPos.getX());
}

/**
 * Sets the servos to a true value (between 0 and 180) even thgough that might
 * might be out of range for the actual setup.
 * @private
 */
void setServosAbsolute(int x, int y)
{
  servoVert.write(y);
  servoHori.write(x);
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    strSerialInput += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      inputComplete = true;
    } 
  }
}

String getValue(String data, char separator, int index)
{
 int found = 0;
  int strIndex[] = {
0, -1  };
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
  if(data.charAt(i)==separator || i==maxIndex){
  found++;
  strIndex[0] = strIndex[1]+1;
  strIndex[1] = (i == maxIndex) ? i+1 : i;
  }
 }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
