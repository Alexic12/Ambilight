#include "led_driver.h"

CRGB leds[NUM_LEDS];
extern String currentCommand;

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

void LedDriver::rainbowCascade(int wait) {
    // Shift the hue across all LEDs, creating a moving rainbow effect
    static uint8_t hue = 0;
    for (int i = 0; i < NUM_LEDS; i++) {
        // Use a different hue for each LED to create the rainbow
        leds[i] = CHSV(hue + (i * 10), 255, 255); // Change the '10' to adjust the rainbow spread
    }
    hue++; // Increment the starting hue to create the cascade effect

    FastLED.show();
    delay(wait); // Wait a bit before moving the rainbow
}

void LedDriver::fadeToColor(CRGB targetColor, int steps, int wait) {
    CRGB currentColor;
    for (int step = 0; step < steps; step++) {
        for (int i = 0; i < NUM_LEDS; i++) {
            // Calculate the intermediate color
            currentColor = leds[i].lerp8(targetColor, (step * 255) / steps);
            leds[i] = currentColor;
        }
        FastLED.show();
        delay(wait); // Control the speed of the fade
    }
}

void LedDriver::movingRainbow(int wait, int rainbowDelta) {
    static uint8_t initialHue = 0;
    for (int i = 0; i < NUM_LEDS; i++) {
        // Calculate the hue for each LED based on its position + the initial hue
        leds[i] = CHSV((initialHue + (i * rainbowDelta)) % 255, 255, 255);
    }
    initialHue++; // Increment the initial hue to create the moving effect

    FastLED.show();
    delay(wait); // Controls the speed of the animation
}

void LedDriver::LedTask(void *pvParameters) {
    (void) pvParameters;
    for (;;) {
        if (currentCommand.equals("RED")) {
            // Set LED strip to RED
            setAllCRGB(CRGB::Red);
        } else if (currentCommand.equals("GREEN")) {
            setAllCRGB(CRGB::Green);
        } else if (currentCommand.equals("BLUE")) {
            setAllCRGB(CRGB::Blue);
        } else if (currentCommand.equals("UV")) {
            setAllCRGB(CRGB::Purple);
        } else if (currentCommand.equals("VIOLET")) {
            setAllCRGB(CRGB::Violet);
        } else if (currentCommand.equals("RAINBOW")) {
            rainbowCascade(10);
        } else if (currentCommand.equals("MOV_RAINBOW")) {
            movingRainbow(10, 5);
        } else if (currentCommand.equals("OFF")) {
            setAllCRGB(CRGB::Black);
        } else {
            // Do nothing
        }

        vTaskDelay(pdMS_TO_TICKS(100)); // Adjust delay as needed
    }
}


// Implement additional methods to control the LEDs as needed