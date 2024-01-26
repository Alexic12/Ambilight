#include "serial_comm.h"


LedDriver ledDriver; // Instantiate the LedDriver class
SerialComm::SerialComm(unsigned long baudRate) {
    _baudRate = baudRate;
}

void SerialComm::init() {
    Serial.begin(_baudRate);
    ledDriver.init(); // Initialize the LedDriver class
    //while (!Serial); // Optionally wait for the serial port to connect - necessary for some devices
}

// Static member function for handling serial communication
void SerialComm::SerialTask(void *pvParameters) {
    (void) pvParameters; // Avoid unused parameter warning
    debugPrint("SerialTask started."); // Use debugPrint here

    String incomingData;
    //
    for (;;) {
        if (Serial.available() > 0) {
            incomingData = Serial.readStringUntil('\n');
            incomingData.trim(); // Remove any leading/trailing whitespace
            debugPrint("Received command: " + incomingData); // Use debugPrint
            //ledDriver.setAllCRGB(CRGB::Red);
            if (incomingData.equals("TEST")) {
                debugPrint("OK");
            }else if(incomingData.equals("RED")){
                debugPrint("RED");
                ledDriver.setAllCRGB(CRGB::Red);
            
            }else if(incomingData.equals("GREEN")){
                debugPrint("GREEN");
                ledDriver.setAllCRGB(CRGB::Green);
            
            }else if(incomingData.equals("BLUE")){
                debugPrint("BLUE");
                ledDriver.setAllCRGB(CRGB::Blue);
            }else {
                debugPrint("Command not recognized."); // Use debugPrint for additional feedback
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10)); // Small delay to prevent task from hogging CPU time
    }
}

// Implement the debugPrint method
void SerialComm::debugPrint(const String &message) {
  if (DEBUG_MODE) {
    Serial.println(message);
  }
}
