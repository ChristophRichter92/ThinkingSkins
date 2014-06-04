//Sound.cpp library for read sound levels from sound board
//author: Christoph

#include "arduino.h"
#include "Sound.h"

//!empty constructor
Sound::Sound()
{
  //pin declaration
  _spectrumReset = 5;
  _spectrumStrobe = 4;
  _spectrumAnalog = 0; //0 for left channel, 1 for right.
  
  //setup sound
  _setupSound();
}

//! pin choice constructor
Sound::Sound(int spectrumReset, int spectrumStrobe, int spectrumAnalog)
{
  _spectrumReset = spectrumReset;
  _spectrumStrobe = spectrumStrobe;
  _spectrumAnalog = spectrumAnalog; 
	
  //setup sound
  _setupSound();
}

//! destructor
Sound::~Sound()
{

}

//! Setup for sound
void Sound::_setupSound()
{
  //Setup pins to drive the spectrum analyzer. 
  pinMode(_spectrumReset, OUTPUT);
  pinMode(_spectrumStrobe, OUTPUT);
 
   //Init spectrum analyzer
  digitalWrite(_spectrumStrobe,LOW);
    delay(1);
  digitalWrite(_spectrumReset,HIGH);
    delay(1);
  digitalWrite(_spectrumStrobe,HIGH);
    delay(1);
  digitalWrite(_spectrumStrobe,LOW);
    delay(1);
  digitalWrite(_spectrumReset,LOW);
    delay(5);
  // Reading the analyzer now will read the lowest frequency. 
}

//! returns current sound spectrum
