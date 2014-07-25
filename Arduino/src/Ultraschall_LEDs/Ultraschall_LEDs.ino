#include <Adafruit_NeoPixel.h>
#include <NewPing.h>

// LEDs
 #define LED_PIN 6 //~
 #define NUMLEDS 9
// Sensor Ultraschall
 #define MAX_DISTANCE 100
 #define ECHO_PIN 7
 #define TRIGGER_PIN  8
 
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_KHZ800 800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
// NEO_KHZ400 400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
// NEO_GRB Pixels are wired for GRB bitstream (most NeoPixel products)
// NEO_RGB Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMLEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop(){
  
  int distance = sonar.ping_cm();
  uint32_t colour = strip.Color(255, 255, 255);
  if(distance != 0){ //distance = 0 => kein gueltiges echo
    if(distance > 90){
      colour = strip.Color(255, 0, 0); //red
    }
    else if(distance > 75){
      colour = strip.Color(0, 0, 255); //blue
    }
    else if(distance > 50){
      colour = strip.Color(0, 255, 0); //green
    }
    else{
      colour = strip.Color(255, 255, 0); //nearer
    }
    
    uint16_t i = 0;
    for(i=0; i<NUMLEDS; i++){
      strip.setPixelColor(i, colour);
    }
  }
  
  //strip.setBrightness(64);
  strip.show();
  delay(100);
}
