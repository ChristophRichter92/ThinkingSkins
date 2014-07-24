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
  // print the string when a newline arrives:
  if (stringComplete) 
  {
    inputString = inputString.substring(0, inputString.length()-1);
    //different commands
    if(inputString == "Hello") //test command
    {
      Serial.println("Hey yo");
    }
    else if(inputString == "Sound") //test command
    {
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
      Serial.println(result);
    }
    else if(inputString == "getDistance()") //read distance
    {
      String result = getDistance();
      Serial.println(result);
    }
    else if(inputString == "on()")  //Backlight on
    {
      //TODO: implementation of turning on (white)
      on();
      Serial.println("ok");
    }
    else if(inputString == "off()") //Backlight off
    {
      off();
      Serial.println("ok");
    }
    else if(inputString.indexOf("changeColor") >= 0) //Backlight change color
    {
      //get cmd params
      //TODO: implementation of changing color
      Serial.println("ok");
    }
    else if(inputString == "open()") //Servos to open pos
    {
      open();
      Serial.println("ok");
    }
    else if(inputString == "close()") //Servos to closed pos
    {
      close();
      Serial.println("ok");
    }
    else if(inputString.indexOf("move") >= 0) //Servos to closed pos
    {
      //TODO pars args
      //move
      Serial.println("ok");
    }
    else if(inputString == "your command")
    {
      //write your command here!
    }
    else
    {
      //default echo
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
  
}

void off()
{
  
}

void changeColor(int r, int g, int b)
{
  
}

//-------------Servos----------
void open()
{
  
}

void close()
{
  
}

//---------Distance--------------
String getDistance()
{
    int distance = sonar.ping_cm();
    return (String)distance;
}
