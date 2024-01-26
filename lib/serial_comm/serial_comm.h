#ifndef SerialComm_h
#define SerialComm_h

#include <Arduino.h>
#include "pin_def.h"
#include "led_driver.h"

class SerialComm {
public:
    SerialComm(unsigned long baudRate);
    void init();
    static void SerialTask(void *pvParameters); // Make SerialTask a static member function
    static void debugPrint(const String &message); // Method for conditional debug messages

private:
    unsigned long _baudRate;
};

#endif
