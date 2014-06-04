// This is a sound driver for adrduino uno with sparkfun spectrum
// shield. 
// author: Christoph
//
// Configuration: 
//
//TODO: convert into library

//golobal variiables

//For spectrum analyzer shield, these three pins are used.
//You can move pins 4 and 5, but you must cut the trace on the shield and re-route from the 2 jumpers. 
int spectrumReset=5;
int spectrumStrobe=4;
int spectrumAnalog=0;  //0 for left channel, 1 for right.

// spectrum analyzer read values will be kept here.
int spectrum[7];

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

void setup() {
  //setup sound
  setupSound();
  
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly: 
  readSpectrum();
  
  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.print(spectrum[0]);
  Serial.print("  ");
  Serial.print(spectrum[1]);
  Serial.print("  ");
  Serial.print(spectrum[2]);
  Serial.print("  ");
  Serial.print(spectrum[3]);
  Serial.print("  ");
  Serial.print(spectrum[4]);
  Serial.print("  ");
  Serial.print(spectrum[5]);
  Serial.print("  ");
  Serial.print(spectrum[6]);
  Serial.print("  ");
  
  Serial.print("\n");
  
  delay(10);  
}

// Read 7 band equalizer.
void readSpectrum()
{
  // Band 0 = Lowest Frequencies.
  byte Band;
  for(Band=0;Band <7; Band++)
  {
    spectrum[Band] = (analogRead(spectrumAnalog) + analogRead(spectrumAnalog) ) >>1; //Read twice and take the average by dividing by 2
    digitalWrite(spectrumStrobe,HIGH);
    digitalWrite(spectrumStrobe,LOW);  
  }
}

