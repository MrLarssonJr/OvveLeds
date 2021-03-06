#include <Adafruit_NeoPixel.h>
#include "Animation.h"
#include "StaticColorAnimation.h"
#include "RainbowAnimation.h"
#include <Vector.h>

//IO config
#define STRIP1_PIN 0
#define STRIP2_PIN 1
#define SWITCH_PIN 2
#define SWITCH_PRESSED LOW
#define INPUT_MODE INPUT_PULLUP

//Animation constants
//TICK_LENGTH refer to a time in ms
#define TICK_LENGTH 100

//Frequently used colors
#define winered 10028293

//mode - referes to the current animation mode
int mode = 0;
//toggled - refers to if the mode has been toggled during this press of the switch.
bool toggled = false;


//Strips
Vector<Adafruit_NeoPixel*> strips;

//Animation objects
Vector<Animation*> animations;

void setup() {
  //Initialise the strips
  strips.push_back(new Adafruit_NeoPixel(15, STRIP1_PIN));
  strips.push_back(new Adafruit_NeoPixel(15, STRIP2_PIN));

  for(int i = 0; i < strips.size(); i++) {
    strips[i] -> begin();
    strips[i] -> show();
  }

  //Initialise animations
  animations.push_back(new StaticColorAnimation(winered));
  animations.push_back(new RainbowAnimation());

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
  /* Record start time
   * For being able to wait an approprieate amount of time at the end of the
   * method.
   */
  unsigned long startTime = millis();

  //Check for switching modes
  if(digitalRead(SWITCH_PIN) == SWITCH_PRESSED) {
    if(!toggled) {
      toggleMode();
    }
  } else {
    toggled = false;
  }

  //Update strips
  for(int i = 0; i < strips.size(); i++) {
    animations[mode] -> tick();

    uint32_t colors[strips[i] -> numPixels()];
    animations[mode] -> getPixelMatrix(i, strips[i] -> numPixels(), colors);

    for(int n = 0; n < strips[i] -> numPixels(); n++) {
      strips[i] -> setPixelColor(n, colors[n]);
    }

    strips[i] -> show();
  }

  //Wait an approprieate amount of time
  delay(TICK_LENGTH - (millis() - startTime));
}

/**
 * Method to toggle the active mode properly.
 *
 * Resets the state so that the next animation can start from the begining.
 * Then switch the current mode.
 */
void toggleMode() {
  toggled = true;
  //Switch mode
  mode = (mode + 1) % animations.size();
}


/**
 * Animation tick logic for the color circle/rainbow effect.
 */
// void tickColorCircleAnimation() {
//   for(int i = 0; i < strip1.numPixels(); i++) {
//     int n = state + i;
//     strip1.setPixelColor(i, R(n), G(n), B(n));
//   }
//   for(int i = 0; i < strip2.numPixels(); i++) {
//     int n = state + i;
//     strip2.setPixelColor(i, R(n), G(n), B(n));
//   }
//
//   state++;
//   state = state % 6*255;
//
//   strip1.show();
//   strip2.show();
// }

/**
 * Animation tick logic for the static wine red animation.
 */
// void tickStaticWineredAnimation() {
//   for(int n = 0; n < strip1.numPixels(); n++) {
//     strip1.setPixelColor(n, winered);
//   }
//   for(int n = 0; n < strip2.numPixels(); n++) {
//     strip2.setPixelColor(n, winered);
//   }
//
//   strip1.show();
//   strip2.show();
// }

/**
 * Animation tick logic for the KIT animation.
 */
// void tickKIT() {
//   int pixels = max(strip1.numPixels(), strip2.numPixels());
//   int internalState = pixels - abs(state - pixels);
//
//   for(int n = 0; n < strip1.numPixels(); n++) {
//     if(internalState - 1 <= n && n <= internalState + 1) {
//       strip1.setPixelColor(n, 255, 0, 0);
//     } else if(internalState - 5 <= n && n <= internalState + 5) {
//       strip1.setPixelColor(n, 127, 0, 0);
//     } else {
//       strip1.setPixelColor(n, 0, 0, 0);
//     }
//   }
//
//   for(int n = 0; n < strip2.numPixels(); n++) {
//     if(internalState - 1 <= n && n <= internalState + 1) {
//       strip2.setPixelColor(n, 255, 0, 0);
//     } else if(internalState - 5 <= n && n <= internalState + 5) {
//       strip2.setPixelColor(n, 127, 0, 0);
//     } else {
//       strip2.setPixelColor(n, 0, 0, 0);
//     }
//   }
//
//   state++;
//   state = state % (2 * pixels);
//
//   strip1.show();
//   strip2.show();
// }

/**
 * Helper method for tickColorCircleAnimation.
 *
 * Calculates the R value of the pixel for the given n.
 * The given roughly responds to led position mixed with state info.
 */
// byte R(int n) {
//   n = n % 6*255;
//   if(n <= 1*255 || 5*255 < 255) {
//     return 255;
//   }
//   else if(1*255 < n && n <= 2*255) {
//     return 255 - (n % 255);
//   }
//   else if(2*255 < n && n <= 4*255) {
//     return 0;
//   }
//   else if(4*255 < n && n <= 5*255) {
//     return n % 255;
//   }
// }

/**
 * Helper method for tickColorCircleAnimation.
 *
 * Calculates the G value of the pixel for the given n.
 * The given roughly responds to led position mixed with state info.
 */
// byte G(int n) {
//   n = n % 6*255;
//   if(n <= 1*255) {
//     return n % 255;
//   }
//   else if(1*255 < n && n <= 3*255) {
//     return 255;
//   }
//   else if(3*255 < n && n <= 4*255) {
//     return 255 - (n % 255);
//   }
//   else if(4*255 < n) {
//     return 0;
//   }
// }

/**
 * Helper method for tickColorCircleAnimation.
 *
 * Calculates the B value of the pixel for the given n.
 * The given roughly responds to led position mixed with state info.
 */
// byte B(int n) {
//   n = n % 6*255;
//   if(n <= 2*255) {
//     return 0;
//   }
//   else if(2*255 < n && n <= 3*255) {
//     return n % 255;
//   }
//   else if(3*255 < n && n <= 5*255) {
//     return 255;
//   }
//   else if(5*255 < n) {
//     return 255 - (n % 255);
//   }
// }
