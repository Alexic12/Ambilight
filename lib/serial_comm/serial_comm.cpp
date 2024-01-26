#include "serial_comm.h"

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
    Serial.println("SerialTask started."); // Debug print
    String incomingData;
    for (;;) {
        if (Serial.available() > 0) {
            incomingData = Serial.readStringUntil('\n');
            incomingData.trim(); // Remove any leading/trailing whitespace
            Serial.print("Received command: "); // Debug print
            Serial.println(incomingData); // Debug print

            if (incomingData.equals("TEST")) {
                Serial.println("OK");
            } else {
                Serial.println("Command not recognized."); // Additional feedback
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10)); // Small delay to prevent task from hogging CPU time
    }
}
