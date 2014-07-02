#include <Sound.h>

/*
*  Description:
*  Main Programm for our Thinking Skin:
*    - react to special commands and executes them
*/

//attributes
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

void setup() //initialize
{  
  // initialize serial:
  Serial.begin(9600);
  digitalWrite(13, LOW); 
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  //setup sound
  setupSound();
}

//main loop
void loop() {  
  // print the string when a newline arrives:
  if (stringComplete) 
  {
    inputString = inputString.substring(0, inputString.length()-1);
    //different commands
    if(inputString == "Hello")
    {
      Serial.println("Hey yo");
    }
    else if(inputString == "Sound")
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
    else if(inputString == "on()")
    {
      //write your command here!
      Serial.println("ok");
    }
    else if(inputString == "off()")
    {
      //write your command here!
      Serial.println("ok");
    }
    else if(inputString.indexOf("changeColor") >= 0)
    {
      //get cmd params
      //write your command here!
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

