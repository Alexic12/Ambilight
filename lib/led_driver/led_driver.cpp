#include "led_driver.h"

CRGB leds[NUM_LEDS];

LedDriver::LedDriver() {
    // Constructor
}

void LedDriver::init() {
    FastLED.addLeds<WS2812B, LED_STRIP_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(50); // Set initial brightness (0-255)
    FastLED.clear(); // Clear any initial data
    FastLED.show(); // Update the strip
}

void LedDriver::setAllCRGB(CRGB color) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = color;
    }
    FastLED.show();
}

// Implement additional methods to control the LEDs as needed