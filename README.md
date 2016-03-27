# OvveLeds
Sketch to animate some Adafruit NeoPixel strips from an Adafruit Gemma board.

This is for a project of LEDifying some student association clothing.

### Dependencies
Adafruit_NeoPixel

### Hardware
Desgined to run on Adafruit Gemma and two Adafruit NeoPixel strips of 15 leds each.
The first strip attached to PIN 0.
The second strip attached to PIN 1.
The switch attached to 2. The switch is considered pressed if the pin recives a LOW voltage.

### Installation
1. Download the latest [relase](https://github.com/MrLarssonJr/OvveLeds/releases).
2. Open in [Arduino IDE](https://www.arduino.cc/en/Main/Software).
  1. Make sure Adafruit_NeoPixel is installed! ([link](https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation))
3. Build and upload to your board.

### Configuring for your hardware
All constants related to the hardware should be easily changed in the .ino file in the release.
