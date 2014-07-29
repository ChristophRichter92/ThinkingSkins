#include <Sound.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include "tsServoDriver.h"
#include <NewPing.h>

/*
*  Description:
*  Main Programm for our Thinking Skin:
*    - react to special commands and executes them
*/

//attributes

// Sensor Ultraschall
 #define MAX_DISTANCE 100
 #define ECHO_PIN 7
 #define TRIGGER_PIN  8
 NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// LEDs
 #define LED_PIN 6 //~
 #define NUMLEDS 9
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_KHZ800 800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
// NEO_KHZ400 400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
// NEO_GRB Pixels are wired for GRB bitstream (most NeoPixel products)
// NEO_RGB Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMLEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

//Servos
Servo servoVert;
Servo servoHori;

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

// global offset variable
Coord offset(HORI_MID, VERT_MID);
int up = 1;
int left = 1;
int xPosition = 0;
int yPosition = 0;


 //Sound
int spectrumReset=5;
int spectrumStrobe=4;
int spectrumAnalog=0;  //0 for left channel, 1 for right.
int band = 0; //used spectrum band
// spectrum analyzer read values will be kept here.
int spectrum[7];

//Sound mySound(5,4,0);
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setupSound() 
{
  //Setup pins to drive the spectrum analyzer. 
  pinMode(spectrumReset, OUTPUT);
  pinMode(spectrumStrobe, OUTPUT);
 
   //Init spectrum analyzer
  digitalWrite(spectrumStrobe,LOW);
    delay(1);
  digitalWrite(spectrumReset,HIGH);
    delay(1);
  digitalWrite(spectrumStrobe,HIGH);
    delay(1);
  digitalWrite(spectrumStrobe,LOW);
    delay(1);
  digitalWrite(spectrumReset,LOW);
    delay(5);
  // Reading the analyzer now will read the lowest frequency. 
}

void setupLED()
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void setupServos()
{
  servoVert.attach(9);  // attaches the servo on pin 9 to the servo object
  servoHori.attach(10);  // attaches the servo on pin 10 to the servo object
}

void setup() //initialize
{  
  // initialize serial:
  Serial.begin(9600);
  digitalWrite(13, LOW); 
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  //setup sound
  setupSound();
  //setup servos
  setupServos();
  //setup led
  setupLED();
  
}

//main loop
void loop() {  
  int delayTime = 100;
  // print the string when a newline arrives:
  if (stringComplete) 
  {
    inputString = inputString.substring(0, inputString.length()-1);
    //different commands
    if(inputString == "Hello") //test command
    {
      delay(delayTime);
      Serial.println("Hey yo");
    }
    else if(inputString == "Sound") //test command
    {
      delay(delayTime);
      Serial.println("Sounds nice :D");
    }
    else if(inputString == "getSound()") //read Soundlevel
    {
      //int spectrum[7];
      readSpectrum();
      String result = "";
      for(int i = 0; i < 7; i++)
      {
        result = result + spectrum[i] + " ";
      }
      delay(delayTime);
      Serial.println(result);
    }
    else if(inputString == "getDistance()") //read distance
    {
      String result = getDistance();
      delay(delayTime);
      Serial.println(result);
    }
    else if(inputString == "on()")  //Backlight on
    {
      on();
      delay(delayTime);
      Serial.println("Backlight on");
    }
    else if(inputString == "off()") //Backlight off
    {
      off();
      delay(delayTime);
      Serial.println("Backlight off");
    }
    else if(inputString.indexOf("changeColor") >= 0) //Backlight change color
    {
      //get cmd params
      int r = parseFirstArg(inputString).toInt();
      int g = parseSecondArg(inputString).toInt();
      int b = parseThirdArg(inputString).toInt();
      //change color
      changeColor(r, g, b);
      delay(delayTime);
      Serial.println("Color changed to: " + (String)r + " " + (String)g + " " + (String)b);
    }
    else if(inputString == "open()") //Servos to open pos
    {
      open();
      delay(delayTime);
      Serial.println("Position: open");
    }
    else if(inputString == "close()") //Servos to closed pos
    {
      close();
      delay(delayTime);
      Serial.println("Position: closed");
    }
    else if(inputString.indexOf("move") >= 0) //Servos to closed pos
    {
      //parse args
      int x = parseFirstArg(inputString).toInt();
      int y = parseThirdArg(inputString).toInt();
      //move
      move(x, y);
      delay(delayTime);
      Serial.println("moved to Position: " + (String)x + " " + (String)y);
    }
    else if(inputString == "present()")
    {
      delay(delayTime);
      Serial.println("Please wait and enjoy the show");
      present();
    }
    else if(inputString == "your command")
    {
      //write your command here!
    }
    else
    {
      //default echo
      delay(delayTime);
      Serial.println(inputString);
    }
    digitalWrite(13, LOW); 
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  else
  {
    //wait for string
    digitalWrite(13, LOW);  
  }
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
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

/*
* Parses the arguments of an command
* nr is the first or second ect. argument
*/
String parseFirstArg(String cmd)
{
    //get args
  int first = cmd.indexOf("(");
  int second = cmd.indexOf(",");
  cmd = cmd.substring(first+1, second);
  
  return cmd;
}

String parseSecondArg(String cmd)
{
    //get args
  int first = cmd.indexOf(",");
  int second = cmd.lastIndexOf(",");
  cmd = cmd.substring(first+1, second);
  return cmd;
}

String parseThirdArg(String cmd)
{
    //get args
  int first = cmd.lastIndexOf(",");
  int second = cmd.indexOf(")");
  cmd = cmd.substring(first+1, second);
  return cmd;
}

//--------Sound----------------
// Read 7 band equalizer.
void readSpectrum()
{
   digitalWrite(spectrumReset, HIGH);
   digitalWrite(spectrumReset, LOW);
    for(band=0; band <7; band++)
    {
      digitalWrite(spectrumStrobe,LOW); // strobe pin on the shield - kicks the IC up to the next band
      delayMicroseconds(30); //
      spectrum[band] = analogRead(0); // store left band reading
      digitalWrite(spectrumStrobe,HIGH);
    }  
}

//----------Backlight-----------
void on()
{
  uint32_t colour = strip.Color(255, 255, 255);
  uint16_t i = 0;
  for(i=0; i<NUMLEDS; i++)
  {
      strip.setPixelColor(i, colour);
  }
  strip.setBrightness(255);
  strip.show();
}

void off()
{
  uint32_t colour = strip.Color(0, 0, 0);
  uint16_t i = 0;
  for(i=0; i<NUMLEDS; i++)
  {
      strip.setPixelColor(i, colour);
  }
  strip.setBrightness(0);
  strip.show();
}

void changeColor(int r, int g, int b)
{
  uint32_t colour = strip.Color(r, g, b);
  uint16_t i = 0;
  for(i=0; i<NUMLEDS; i++)
  {
      strip.setPixelColor(i, colour);
  }
  strip.setBrightness(255);
  strip.show();
}

//-------------Servos----------
void open()
{
  move(0,0);
}

void close()
{
  move(255,255);
}

void move(int x, int y)
{
  Coord newPos = Coord(x,y);
  //get distance
  int steps = 10;
  int dx = x-xPosition;
  int dy = y-yPosition;
  int xStepSize = dx/steps;
  int yStepSize = dy/steps;
  
  int i = 0;
  while(i<steps)
  {
    xPosition += xStepSize;
    yPosition += yStepSize;
    newPos = Coord(xPosition, yPosition);
    setServos(newPos);
    i++;
    delay(30);  
  }
  //setServos(newPos);
}

void setServos(Coord newPos)
{
  //Serial.println(newPos.getX());
  //Serial.println(newPos.getX()/255);
  //Serial.println(round(( (float)newPos.getX()/255 ) * HORI_RANGE));
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

void present()
{
  int i = 0;
  while(i < 1000)
  {
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
    i++;
    delay(15);
  } 
}

//---------Distance--------------
String getDistance()
{
    int distance = sonar.ping_cm();
    return (String)distance;
}
