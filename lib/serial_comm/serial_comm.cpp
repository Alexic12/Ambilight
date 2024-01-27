#include "serial_comm.h"



extern String currentCommand;

SerialComm::SerialComm(unsigned long baudRate) {
    _baudRate = baudRate;
}

void SerialComm::init() {
    Serial.begin(_baudRate);
    
    //while (!Serial); // Optionally wait for the serial port to connect - necessary for some devices
}
void SerialComm::initMessage() {
    Serial.println("Ambilight System Initializing...");
    delay(500);
    Serial.println("-----------------------------");
    Serial.println("Debug mode: ON");
    Serial.println("System initialization complete!");
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
            if (incomingData.equals("PING")) {
                debugPrint("I'M ALIVE!");
            } else {
                currentCommand = incomingData;
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
