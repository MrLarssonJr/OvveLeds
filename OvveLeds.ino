#include <Adafruit_NeoPixel.h>

//IO config
#define STRIP1_PIN 0
#define STRIP2_PIN 1
#define SWITCH_PIN 2
#define SWITCH_PRESSED LOW

//Different animation modes
#define MODE_COLOR_CIRCLE 0
#define MODE_STATIC_WINERED 666 

//Animation constants
//TICK_LENGTH refer to a time in ms
#define TICK_LENGTH 10

//mode - referes to the current animation mode
int mode = MODE_COLOR_CIRCLE;
//state - refers to the state of the current animation. 0 refers to start of animation.
int state = 0;

//Strips
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(15, STRIP1_PIN);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(15, STRIP2_PIN);

//Frequently used colors
uint32_t winered = strip1.Color(153, 0, 18);

void setup() {
  //Initialise the strips
  strip1.begin();
  strip2.begin();
  strip1.show();
  strip2.show();

  //Setup the SWITCH_PIN as an INPUT
  pinMode(SWITCH_PIN, INPUT);
}

void loop() {
  unsigned long startTime = millis();
  
  if(digitalRead(SWITCH_PIN) == SWITCH_PRESSED) {
    toggleMode();
  }

  switch(mode) {
    case MODE_COLOR_CIRCLE:
      tickColorCircleAnimation();
      break;
    case MODE_STATIC_WINERED:
      tickStaticWineredAnimation();
      break;
  }
  
  delay(TICK_LENGTH - (millis() - startTime));
}

void tickColorCircleAnimation() {
  for(int i = 0; i < strip1.numPixels(); i++) {
    int n = state + i;
    strip1.setPixelColor(i, R(n), G(n), B(n));
  }
  for(int i = 0; i < strip2.numPixels(); i++) {
    int n = state + i;
    strip2.setPixelColor(i, R(n), G(n), B(n));
  }

  state++;
  state = state % 6*255;

  strip1.show();
  strip2.show();
}

void tickStaticWineredAnimation() {
  for(int n = 0; n < strip1.numPixels(); n++) {
    strip1.setPixelColor(n, winered);
  }
  for(int n = 0; n < strip2.numPixels(); n++) {
    strip2.setPixelColor(n, winered);
  }

  strip1.show();
  strip2.show();
}

void toggleMode() {
  //Reset the state so the next animation can start from the begining.
  state = 0;
  //Switch mode
  switch(mode) {
    case MODE_COLOR_CIRCLE:
      mode = MODE_STATIC_WINERED;
      break;
    case MODE_STATIC_WINERED:
      mode = MODE_COLOR_CIRCLE;
      break;
    default:
      mode = MODE_STATIC_WINERED;
      break;
  }
}

byte R(int n) {
  n = n % 6*255;
  if(n <= 1*255 || 5*255 < 255) {
    return 255;
  }
  else if(1*255 < n && n <= 2*255) {
    return 255 - (n % 255);
  }
  else if(2*255 < n && n <= 4*255) {
    return 0;
  }
  else if(4*255 < n && n <= 5*255) {
    return n % 255;
  }
}

byte G(int n) {
  n = n % 6*255;
  if(n <= 1*255) {
    return n % 255;
  }
  else if(1*255 < n && n <= 3*255) {
    return 255;
  }
  else if(3*255 < n && n <= 4*255) {
    return 255 - (n % 255);
  }
  else if(4*255 < n) {
    return 0;
  }
}

byte B(int n) {
  n = n % 6*255;
  if(n <= 2*255) {
    return 0;
  }
  else if(2*255 < n && n <= 3*255) {
    return n % 255;
  }
  else if(3*255 < n && n <= 5*255) {
    return 255;
  }
  else if(5*255 < n) {
    return 255 - (n % 255);
  }
}

