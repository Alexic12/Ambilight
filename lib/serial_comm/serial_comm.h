#ifndef SerialComm_h
#define SerialComm_h

#include <Arduino.h>

class SerialComm {
public:
    SerialComm(unsigned long baudRate);
    void init();
    static void SerialTask(void *pvParameters); // Make SerialTask a static member function

private:
    unsigned long _baudRate;
};

#endif
