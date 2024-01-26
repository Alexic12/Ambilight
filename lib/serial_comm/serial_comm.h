// SerialComm.h
#ifndef SerialComm_h
#define SerialComm_h

#include <Arduino.h>

class SerialComm {
  public:
    SerialComm(unsigned long baudRate);
    void init();
    void checkSerial();
  private:
    unsigned long _baudRate;
};

#endif
