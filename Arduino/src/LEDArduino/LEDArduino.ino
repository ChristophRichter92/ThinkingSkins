// Library: https://github.com/adafruit/Adafruit_NeoPixel
// Tutorial: https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library

#include <Adafruit_NeoPixel.h>

 #define PIN 6
 
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_KHZ800 800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
// NEO_KHZ400 400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
// NEO_GRB Pixels are wired for GRB bitstream (most NeoPixel products)
// NEO_RGB Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(3, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop(){
  uint32_t red = strip.Color(255, 0, 0);
  uint32_t blue = strip.Color(0, 0, 255);
  uint32_t green = strip.Color(0, 255, 0);
  strip.setPixelColor(0, green);
  strip.setPixelColor(1, red);
  strip.setPixelColor(2, blue);
  strip.setBrightness(64);
  strip.show();
}
