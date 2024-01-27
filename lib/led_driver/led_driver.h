#ifndef LedDriver_h
#define LedDriver_h

#include <Arduino.h>
#include <FastLED.h>
#include "pin_def.h"
#include "color_def.h"
#include "serial_comm.h"

class LedDriver {
public:
 

    LedDriver();
    void init();
    static void setAllCRGB(CRGB color);
    static void rainbowCascade(int wait);
    static void fadeToColor(CRGB targetColor, int steps, int wait);
    static void movingRainbow(int wait, int rainbowDelta); 
    static void LedTask(void *pvParameters); //freeRTOS task function for LedDriver
    
    
};

#endif
