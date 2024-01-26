#ifndef LedDriver_h
#define LedDriver_h

#include <Arduino.h>
#include <FastLED.h>
#include "pin_def.h"

class LedDriver {
public:
    LedDriver();
    void init();
    void setAllCRGB(CRGB color);
    // Add more functions here as needed
};

#endif