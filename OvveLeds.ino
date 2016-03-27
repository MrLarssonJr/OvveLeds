#include <Adafruit_NeoPixel.h>

//IO config
#define STRIP1_PIN 0
#define STRIP2_PIN 1
#define SWITCH_PIN 2
#define SWITCH_PRESSED LOW

//Different animation modes
#define MODE_COLOR_CIRCLE 0
#define MODE_STATIC_WINERED 666 

//mode - referes to the current animation mode
int mode = MODE_STATIC_WINERED;

//Strips
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(15, STRIP1_PIN);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(15, STRIP2_PIN);


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
  if(digitalRead(SWITCH_PIN) == SWITCH_PRESSED) {
    toggleMode();
  }

  
}

void toggleMode() {
  switch(mode) {
    case MODE_COLOR_CIRCLE:
      mode = MODE_STATIC_WINERED;
      break;
    case MODE_STATIC_WINERED:
      mode = MODE_COLOR_CIRCLE;
      break;
  }
}

