#ifndef SerialComm_h
#define SerialComm_h

#include <Arduino.h>
#include "pin_def.h"


class SerialComm {
public:
    SerialComm(unsigned long baudRate);
    void init();
    static void SerialTask(void *pvParameters); // serial communications freeRTOS function
    static void debugPrint(const String &message); // Method for conditional debug messages
    void initMessage();

private:
    unsigned long _baudRate;
};

#endif
