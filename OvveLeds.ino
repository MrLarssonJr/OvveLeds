#include <Adafruit_NeoPixel.h>

//IO config
#define STRIP1_PIN 0
#define STRIP2_PIN 1
#define SWITCH_PIN 2
#define SWITCH_PRESSED LOW
#define INPUT_MODE INPUT_PULLUP

//Different animation modes
#define MODE_COLOR_CIRCLE 0
#define MODE_STATIC_WINERED 666 

//Animation constants
//TICK_LENGTH refer to a time in ms
#define TICK_LENGTH 100

//mode - referes to the current animation mode
int mode = MODE_COLOR_CIRCLE;
//state - refers to the state of the current animation. 0 refers to start of animation.
int state = 0;
//toggled - refers to if the mode has been toggled during this press of the switch.
bool toggled = false;

//Strips
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(15, STRIP1_PIN);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(15, STRIP2_PIN);

//Frequently used colors
uint32_t winered = strip1.Color(153, 5, 5);

void setup() {
  //Initialise the strips
  strip1.begin();
  strip2.begin();
  strip1.show();
  strip2.show();

  //Setup the SWITCH_PIN as an INPUT
  pinMode(SWITCH_PIN, INPUT_MODE);
}

/**
 * Main loop.
 * 
 * Checks if the button was pressed and then toggles the mode.
 * Allows one effect calculates it's logic and push color to the strips.
 * 
 * Tries to keep each loop's length to TICK_LENGTH
 */
void loop() {
  unsigned long startTime = millis();

  if(digitalRead(SWITCH_PIN) == SWITCH_PRESSED) {
    if(!toggled) {
      toggleMode();
    }
  } else {
    toggled = false;
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

/**
 * Animation tick logic for the color circle/rainbow effect.
 */
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

/**
 * Animation tick logic for the static wine red animation.
 */
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

/**
 * Method to toggle the active mode properly.
 * 
 * Resets the state so that the next animation can start from the begining.
 * Then switch the current mode.
 */
void toggleMode() {
  toggled = true;
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

/**
 * Helper method for tickColorCircleAnimation.
 * 
 * Calculates the R value of the pixel for the given n.
 * The given roughly responds to led position mixed with state info.
 */
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

/**
 * Helper method for tickColorCircleAnimation.
 * 
 * Calculates the G value of the pixel for the given n.
 * The given roughly responds to led position mixed with state info.
 */
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

/**
 * Helper method for tickColorCircleAnimation.
 * 
 * Calculates the B value of the pixel for the given n.
 * The given roughly responds to led position mixed with state info.
 */
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

