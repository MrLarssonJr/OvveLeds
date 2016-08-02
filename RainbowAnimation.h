#ifndef RainbowAnimation_h
#define RainbowAnimation_h

#include "Animation.h"
#include "Arduino.h"

class RainbowAnimation : public Animation {
private:
  int _state;
  uint8_t r(int n);
  uint8_t g(int n);
  uint8_t b(int n);
public:
  RainbowAnimation();
  void tick();
  void getPixelMatrix(int strip, int pixels, uint32_t *colors);
};

#endif
