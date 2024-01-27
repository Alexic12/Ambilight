#include <FastLED.h>

// A simple struct to hold the color name and its corresponding CRGB value
struct ColorMap {
    const char* name;
    const CRGB color;
};

// An array of ColorMap structs for the colors you want to support
const ColorMap colorMap[] = {
    {"RED", CRGB::Red},
    {"GREEN", CRGB::Green},
    {"BLUE", CRGB::Blue},
    {"YELLOW", CRGB::Yellow},
    {"ORANGE", CRGB::Orange},
    {"PURPLE", CRGB::Purple},
    {"AMETHYST", CRGB::Amethyst},
    // Add more colors as needed
};
const int colorMapSize = sizeof(colorMap) / sizeof(colorMap[0]); // Number of elements in colorMap
