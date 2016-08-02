#ifndef StaticColorAnimation_h
#define StaticColorAnimation_h

#include "Animation.h"
#include "Arduino.h"

class StaticColorAnimation : public Animation {
private:
  uint32_t _color;
public:
  StaticColorAnimation(uint32_t color);
  void tick();
  void getPixelMatrix(int strip, int pixels, uint32_t *colors);
};

#endif
