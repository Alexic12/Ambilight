// SerialComm.cpp
#include "serial_comm.h"

SerialComm::SerialComm(unsigned long baudRate) {
  _baudRate = baudRate;
}

void SerialComm::init() {
  Serial.begin(_baudRate);
  //while (!Serial); // Wait for the serial port to connect - necessary for some devices
}

void SerialComm::checkSerial() {
  if (Serial.available() > 0) {
    String incomingData = Serial.readStringUntil('\n');
    incomingData.trim(); // Remove any leading/trailing whitespace
    
    if (incomingData.equals("TEST")) {
      Serial.println("OK");
    }
  }
}
