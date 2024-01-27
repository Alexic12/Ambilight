#include "serial_comm.h"



extern String currentCommand;

SerialComm::SerialComm(unsigned long baudRate) {
    _baudRate = baudRate;
}

void SerialComm::init() {
    Serial.begin(_baudRate);
    
    //while (!Serial); // Optionally wait for the serial port to connect - necessary for some devices
}

// Static member function for handling serial communication
void SerialComm::SerialTask(void *pvParameters) {
    (void) pvParameters; // Avoid unused parameter warning
    debugPrint("SerialTask started."); // Use debugPrint here

    String incomingData;
    for (;;) {
        if (Serial.available() > 0) {
            incomingData = Serial.readStringUntil('\n');
            incomingData.trim(); // Remove any leading/trailing whitespace
            debugPrint("Received command: " + incomingData); // Use debugPrint

            // Map command string to animation type and set it
            if (incomingData.equals("TEST")) {
                debugPrint("OK");
            } else if (incomingData.equals("RED")) {
                currentCommand = "RED"; // Set the global variable
            } else if (incomingData.equals("GREEN")) {
                currentCommand = "GREEN";
            } else if (incomingData.equals("BLUE")) {
                currentCommand = "BLUE";
            } else if (incomingData.equals("UV")) {
                currentCommand = "UV";
            } else if (incomingData.equals("VIOLET")) {
                currentCommand = "VIOLET";
            } else if (incomingData.equals("RAINBOW")) {
                currentCommand = "RAINBOW";
            } else if (incomingData.equals("MOV_RAINBOW")) {
                currentCommand = "MOV_RAINBOW";
            } else if (incomingData.equals("OFF")) {
                currentCommand = "OFF";
            } else {
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
