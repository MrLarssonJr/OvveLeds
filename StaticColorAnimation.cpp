#include "Arduino.h"
#include "StaticColorAnimation.h"

StaticColorAnimation::StaticColorAnimation(uint32_t color):Animation() {
  _color = color;
}

void StaticColorAnimation::tick() {}

void StaticColorAnimation::getPixelMatrix(int strip, int pixels, uint32_t *colors) {
  for(int i = 0; i < pixels; ++i) {
    colors[i] = _color;
  }
}
