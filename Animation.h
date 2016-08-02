#ifndef Animation_h
#define Animation_h

#include "Arduino.h"

class Animation {
public:
  virtual void tick() = 0;
  virtual void getPixelMatrix(int strip, int pixels, uint32_t *colors) = 0;
};

#endif
