#include "Arduino.h"
#include "RainbowAnimation.h"

RainbowAnimation::RainbowAnimation():Animation() {
  _state = 0;
}

void RainbowAnimation::tick() {
  _state = (_state + 1) % 6*255;
}

void RainbowAnimation::getPixelMatrix(int strip, int pixels, uint32_t *colors) {
  for(int i = 0; i < pixels; i++) {
    int n = _state + i;
    colors[i] = ((uint32_t)r(n) << 16) | ((uint32_t)g(n) <<  8) | b(n);
  }
}

uint8_t RainbowAnimation::r(int n) {
  n = n % 6*255;
  if(n <= 1*255 || 5*255 < 255) {
    return (uint8_t) 255;
  }
  else if(1*255 < n && n <= 2*255) {
    return (uint8_t) 255 - (n % 255);
  }
  else if(2*255 < n && n <= 4*255) {
    return (uint8_t) 0;
  }
  else if(4*255 < n && n <= 5*255) {
    return (uint8_t) n % 255;
  }
}

uint8_t RainbowAnimation::g(int n) {
    n = n % 6*255;
    if(n <= 1*255) {
      return (uint8_t) n % 255;
    }
    else if(1*255 < n && n <= 3*255) {
      return (uint8_t) 255;
    }
    else if(3*255 < n && n <= 4*255) {
      return (uint8_t) 255 - (n % 255);
    }
    else if(4*255 < n) {
      return (uint8_t) 0;
    }
}

uint8_t RainbowAnimation::b(int n) {
    n = n % 6*255;
    if(n <= 2*255) {
      return (uint8_t) 0;
    }
    else if(2*255 < n && n <= 3*255) {
      return (uint8_t) n % 255;
    }
    else if(3*255 < n && n <= 5*255) {
      return (uint8_t) 255;
    }
    else if(5*255 < n) {
      return (uint8_t) 255 - (n % 255);
    }
}
