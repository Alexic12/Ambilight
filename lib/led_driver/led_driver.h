#ifndef LedDriver_h
#define LedDriver_h

#include <Arduino.h>
#include <FastLED.h>
#include "pin_def.h"

class LedDriver {
public:
 

    LedDriver();
    void init();
    static void setAllCRGB(CRGB color);
    static void rainbowCascade(int wait);
    static void fadeToColor(CRGB targetColor, int steps, int wait);
    static void movingRainbow(int wait, int rainbowDelta);
    static void LedTask(void *pvParameters); // Simplified to a single declaration

    enum class LedAnimation {
        NONE,
        RED_FADE,
        GREEN_FADE,
        BLUE_FADE,
        UV_FADE,
        VIOLET_FADE,
        RAINBOW_CASCADE,
        MOVING_RAINBOW,
        OFF
    };
    
    
private:
    
    LedAnimation currentAnimation = LedAnimation::NONE;
    
    
};

#endif
