//Sound.h library for read sound levels from sound board
//author: Christoph
#ifndef Sound_h
#define Sound_h

#include "Arduino.h"

class Sound
{
	public:
		//! empty constructor
		Sound();
		//! constructor with pin choice
		Sound(int spectrumReset, int spectrumStrobe, int spectrumAnalog);
		//!destructor
		~Sound();
		//! get current sound spectrum
		void getSoundSpectrum(int spectrum[7]);
		
	private:
		//attributes
		int _spectrum[7];
		int _spectrumReset;
		int _spectrumStrobe;
		int _spectrumAnalog;  //0 for left channel, 1 for right.
		
		//functions
		void _setupSound();
};

#endif
