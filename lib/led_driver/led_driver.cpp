#include "led_driver.h"

CRGB leds[NUM_LEDS];
extern String currentCommand;
extern SerialComm S;
bool cmd_flag = false;

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
    if(cmd_flag == true){
        for (int step = 0; step < steps; step++) {
            for (int i = 0; i < NUM_LEDS; i++) {
                // Calculate the intermediate color
                currentColor = leds[i].lerp8(targetColor, (step * 255) / steps);
                leds[i] = currentColor;
            }
            FastLED.show();
            delay(wait); // Control the speed of the fade
            S.debugPrint("fade");
            //print steps
            S.debugPrint("Step: " + String(step));

        }
    }
    cmd_flag = false;
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
            cmd_flag = true;
            fadeToColor(CRGB::Red, 50, 40);
        } else if (currentCommand.equals("GREEN")) {
            cmd_flag = true;
            fadeToColor(CRGB::Green, 50, 40);
        } else if (currentCommand.equals("BLUE")) {
            cmd_flag = true;
            fadeToColor(CRGB::Blue, 50, 40);
        } else if (currentCommand.equals("YELLOW")) {
            cmd_flag = true;
            fadeToColor(CRGB::Yellow, 50, 40);
        } else if (currentCommand.equals("ORANGE")) {
            cmd_flag = true;
            fadeToColor(CRGB::Orange, 50, 40);
        } else if (currentCommand.equals("PURPLE")) {
            cmd_flag = true;
            fadeToColor(CRGB::Purple, 50, 40);
        } else if (currentCommand.equals("AMETHYST")) {
            cmd_flag = true;
            fadeToColor(CRGB::Amethyst, 50, 40);
        } else if (currentCommand.equals("AQUA")) {
            cmd_flag = true;
            fadeToColor(CRGB::Aqua, 50, 40);
        } else if (currentCommand.equals("AZURE")) {
            cmd_flag = true;
            fadeToColor(CRGB::Azure, 50, 40);
        } else if (currentCommand.equals("BLACK")) {
            cmd_flag = true;
            fadeToColor(CRGB::Black, 50, 40);
        } else if (currentCommand.equals("BLUEVIOLET")) {
            cmd_flag = true;
            fadeToColor(CRGB::BlueViolet, 50, 40);
        } else if (currentCommand.equals("CHARTREUSE")) {
            cmd_flag = true;
            fadeToColor(CRGB::Chartreuse, 50, 40);
        } else if (currentCommand.equals("CORAL")) {
            cmd_flag = true;
            fadeToColor(CRGB::Coral, 50, 40);
        } else if (currentCommand.equals("CYAN")) {
            cmd_flag = true;
            fadeToColor(CRGB::Cyan, 50, 40);
        }else if (currentCommand.equals("DARKBLUE")) {
            cmd_flag = true;
            fadeToColor(CRGB::DarkBlue, 50, 40);
        } else if (currentCommand.equals("DARKCYAN")) {
            cmd_flag = true;
            fadeToColor(CRGB::DarkCyan, 50, 40);
        } else if (currentCommand.equals("DARKGREEN")) {
            cmd_flag = true;
            fadeToColor(CRGB::DarkGreen, 50, 40);
        } else if (currentCommand.equals("DARKORANGE")) {
            cmd_flag = true;
            fadeToColor(CRGB::DarkOrange, 50, 40);
        } else if (currentCommand.equals("DARKRED")) {
            cmd_flag = true;
            fadeToColor(CRGB::DarkRed, 50, 40);
        } else if (currentCommand.equals("DEEPSKYBLUE")) {
            cmd_flag = true;
            fadeToColor(CRGB::DeepSkyBlue, 50, 40);
        } else if (currentCommand.equals("DODGERBLUE")) {
            cmd_flag = true;
            fadeToColor(CRGB::DodgerBlue, 50, 40);
        } else if (currentCommand.equals("FIREBRICK")) {
            cmd_flag = true;
            fadeToColor(CRGB::FireBrick, 50, 40);
        } else if (currentCommand.equals("FUCHSIA")) {
            cmd_flag = true;
            fadeToColor(CRGB::Fuchsia, 50, 40);
        } else if (currentCommand.equals("GOLD")) {
            cmd_flag = true;
            fadeToColor(CRGB::Gold, 50, 40);
        } else if (currentCommand.equals("GOLDENROD")) {
            cmd_flag = true;
            fadeToColor(CRGB::Goldenrod, 50, 40);
        } else if (currentCommand.equals("GRAY")) {
            cmd_flag = true;
            fadeToColor(CRGB::Gray, 50, 40);
        } else if (currentCommand.equals("GREENYELLOW")) {
            cmd_flag = true;
            fadeToColor(CRGB::GreenYellow, 50, 40);
        } else if (currentCommand.equals("HOTPINK")) {
            cmd_flag = true;
            fadeToColor(CRGB::HotPink, 50, 40);
        } else if (currentCommand.equals("INDIANRED")) {
            cmd_flag = true;
            fadeToColor(CRGB::IndianRed, 50, 40);
        } else if (currentCommand.equals("INDIGO")) {
            cmd_flag = true;
            fadeToColor(CRGB::Indigo, 50, 40);
        } else if (currentCommand.equals("LAVENDER")) {
            cmd_flag = true;
            fadeToColor(CRGB::Lavender, 50, 40);
        } else if (currentCommand.equals("LIGHTBLUE")) {
            cmd_flag = true;
            fadeToColor(CRGB::LightBlue, 50, 40);
        } else if (currentCommand.equals("LIGHTCORAL")) {
            cmd_flag = true;
            fadeToColor(CRGB::LightCoral, 50, 40);
        }
        // Add special patterns here
        else if (currentCommand.equals("RAINBOW")) {
            rainbowCascade(10);
        } else if (currentCommand.equals("MOV_RAINBOW")) {
            movingRainbow(10, 5);
        }else if(currentCommand.equals("OFF")){
            cmd_flag = true;
            fadeToColor(CRGB::Black, 50, 40);
        }
        //reset currentCommand
        if(cmd_flag){
            currentCommand = "";
        }
        
        vTaskDelay(pdMS_TO_TICKS(10)); // Adjust delay as needed
    }
}


// Implement additional methods to control the LEDs as needed