#include <Sound.h>

/*
*  Description:
*  Main Programm for our Thinking Skin:
*    - react to special commands and executes them
*/

//attributes
//Sound mySound(5,4,0);
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() //initialize
{  
  // initialize serial:
  Serial.begin(9600);
  digitalWrite(13, LOW); 
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
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
      int spectrum[7];
      //mySound.getSoundSpectrum(spectrum);
      String result = "";
      for(int i = 0; i < 7; i++)
      {
        result = result + spectrum[i];
      }
      Serial.println(result);
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


