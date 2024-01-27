#include "led_driver.h"

CRGB leds[NUM_LEDS];
extern String currentCommand;
extern SerialComm S;

LedDriver::LedDriver() {
    // Constructor
}

void LedDriver::init() {
    FastLED.addLeds<WS2812B, LED_STRIP_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(50); // Set initial brightness (0-255)
    FastLED.clear(); // Clear any initial data
    FastLED.show(); // Update the strip
    //S.debugPrint("Color map size: " + int(colorMapSize)); // Print the size of the color map (defined in color_def.h)
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
    S.debugPrint("LedTask started."); // Use debugPrint here
    for (;;) {
        // Map command string to animation type and set it
        if (currentCommand.equals("RED")) {
            fadeToColor(CRGB::Red, 50, 100);
        } else if (currentCommand.equals("GREEN")) {
            fadeToColor(CRGB::Green, 50, 100);
        } else if (currentCommand.equals("BLUE")) {
            fadeToColor(CRGB::Blue, 50, 100);
        } else if (currentCommand.equals("YELLOW")) {
            fadeToColor(CRGB::Yellow, 50, 100);
        } else if (currentCommand.equals("ORANGE")) {
            fadeToColor(CRGB::Orange, 50, 100);
        } else if (currentCommand.equals("PURPLE")) {
            fadeToColor(CRGB::Purple, 50, 100);
        } else if (currentCommand.equals("AMETHYST")) {
            fadeToColor(CRGB::Amethyst, 50, 100);
        } else if (currentCommand.equals("AQUA")) {
            fadeToColor(CRGB::Aqua, 50, 100);
        } else if (currentCommand.equals("AZURE")) {
            fadeToColor(CRGB::Azure, 50, 100);
        } else if (currentCommand.equals("BLACK")) {
            fadeToColor(CRGB::Black, 50, 100);
        } else if (currentCommand.equals("BLUEVIOLET")) {
            fadeToColor(CRGB::BlueViolet, 50, 100);
        } else if (currentCommand.equals("CHARTREUSE")) {
            fadeToColor(CRGB::Chartreuse, 50, 100);
        } else if (currentCommand.equals("CORAL")) {
            fadeToColor(CRGB::Coral, 50, 100);
        } else if (currentCommand.equals("CYAN")) {
            fadeToColor(CRGB::Cyan, 50, 100);
        }else if (currentCommand.equals("DARKBLUE")) {
            fadeToColor(CRGB::DarkBlue, 50, 100);
        } else if (currentCommand.equals("DARKCYAN")) {
            fadeToColor(CRGB::DarkCyan, 50, 100);
        } else if (currentCommand.equals("DARKGREEN")) {
            fadeToColor(CRGB::DarkGreen, 50, 100);
        } else if (currentCommand.equals("DARKORANGE")) {
            fadeToColor(CRGB::DarkOrange, 50, 100);
        } else if (currentCommand.equals("DARKRED")) {
            fadeToColor(CRGB::DarkRed, 50, 100);
        } else if (currentCommand.equals("DEEPSKYBLUE")) {
            fadeToColor(CRGB::DeepSkyBlue, 50, 100);
        } else if (currentCommand.equals("DODGERBLUE")) {
            fadeToColor(CRGB::DodgerBlue, 50, 100);
        } else if (currentCommand.equals("FIREBRICK")) {
            fadeToColor(CRGB::FireBrick, 50, 100);
        } else if (currentCommand.equals("FUCHSIA")) {
            fadeToColor(CRGB::Fuchsia, 50, 100);
        } else if (currentCommand.equals("GOLD")) {
            fadeToColor(CRGB::Gold, 50, 100);
        } else if (currentCommand.equals("GOLDENROD")) {
            fadeToColor(CRGB::Goldenrod, 50, 100);
        } else if (currentCommand.equals("GRAY")) {
            fadeToColor(CRGB::Gray, 50, 100);
        } else if (currentCommand.equals("GREENYELLOW")) {
            fadeToColor(CRGB::GreenYellow, 50, 100);
        } else if (currentCommand.equals("HOTPINK")) {
            fadeToColor(CRGB::HotPink, 50, 100);
        } else if (currentCommand.equals("INDIANRED")) {
            fadeToColor(CRGB::IndianRed, 50, 100);
        } else if (currentCommand.equals("INDIGO")) {
            fadeToColor(CRGB::Indigo, 50, 100);
        } else if (currentCommand.equals("LAVENDER")) {
            fadeToColor(CRGB::Lavender, 50, 100);
        } else if (currentCommand.equals("LIGHTBLUE")) {
            fadeToColor(CRGB::LightBlue, 50, 100);
        } else if (currentCommand.equals("LIGHTCORAL")) {
            fadeToColor(CRGB::LightCoral, 50, 100);
        }
        // Add special patterns here
        else if (currentCommand.equals("RAINBOW")) {
            rainbowCascade(10);
        } else if (currentCommand.equals("MOV_RAINBOW")) {
            movingRainbow(10, 5);
        }else if(currentCommand.equals("OFF")){
            fadeToColor(CRGB::Black, 50, 100);
        }

        vTaskDelay(pdMS_TO_TICKS(10)); // Adjust delay as needed
    }
}


// Implement additional methods to control the LEDs as needed