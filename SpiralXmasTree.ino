#include <Adafruit_NeoPixel.h>

#define PIN 6
#define PIXELS 44

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t red   = strip.Color(255, 0, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t blue  = strip.Color(0, 0, 255);
uint32_t orange = strip.Color(255, 128, 0);
uint32_t purple = strip.Color(128, 0, 255);
uint32_t CLEAN = strip.Color(0, 0, 0);

void setup() {
  strip.begin();
  strip.setBrightness(70);
  randomSeed(analogRead(0));
}


void full(uint32_t color) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void fade(uint32_t color) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  for(int j=1;j<70;j++){
    strip.setBrightness(j);    
    strip.show();
    delay(10);
  }
  for(int j=70;j>0;j--){
    strip.setBrightness(j);    
    strip.show();
    delay(10);
  }
  strip.setBrightness(70); 
}
void ascend(uint32_t color, int wait = random(1,10)) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void descend(uint32_t color, int wait = random(1,10)) {
  for (int16_t i = strip.numPixels() - 1; i >= 0; i--) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void ascendRandom(int wait = random(1,10)) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    uint32_t c = randomColor();
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void descendRandom(int wait = random(1,10)) {
  for (int16_t i = strip.numPixels() - 1; i >= 0; i--) {
    uint32_t c = randomColor();
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

uint32_t randomSparks() {
  for(int j=0;j<5;j++){
    for (uint16_t i = 0; i < strip.numPixels() - 1; i++) {
      uint32_t c = randomColor();
      if (randomChoice())
        strip.setPixelColor(i, c);
      else
        strip.setPixelColor(i, CLEAN);
    }
    strip.show();
    delay(500);
  }
}

void switching(uint32_t colorA, uint32_t colorB) {
  for (int j = 0; j < 5; j++) {
    for (int16_t i = strip.numPixels() - 1; i >= 0; i--) {
      if (i >= strip.numPixels()/2) {
        strip.setPixelColor(i, colorA);
      } else {
        strip.setPixelColor(i, colorB);
      }
    }
    strip.show();
    delay(250);
    for (int16_t i = strip.numPixels() - 1; i >= 0; i--) {
      if (i >= strip.numPixels()/2) {
        strip.setPixelColor(i, colorB);
      } else {
        strip.setPixelColor(i, colorA);
      }
    }
    strip.show();
    delay(250);
  }
}

uint32_t randomColor() {
  int r = random(0, 255);
  int g = random(0, 255);
  int b = random(0, 255);
  uint32_t c = strip.Color(r, g, b);
  return c;
}

bool randomChoice() {
  return random(0, 10) > 4;
}



void loop() {
  switch(random(0,15)){
    case 0: full(randomColor()); ;break;
    case 1: ascend(randomColor()); ;break;
    case 2: descend(randomColor()); ;break;
    case 3: ascendRandom(); ;break;
    case 4: descendRandom(); ;break;
    case 5: ascend(red); ;break;
    case 6: descend(green); ;break;
    case 7: ascend(CLEAN); ;break;
    case 8: descend(CLEAN); ;break;
    case 9: randomSparks(); ;break;
    case 10: switching(purple, orange); ;break;    
    case 11: switching(red, green); ;break;    
    case 12: switching(randomColor(), randomColor()); ;break;    
    case 13: fade(randomColor()); ;break;
    case 14: full(CLEAN); ;break;    
  }
  delay(random(100, 500));
}
