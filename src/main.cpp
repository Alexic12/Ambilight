#include <Arduino.h>
//#include "serial_comm.h" // Include the SerialComm class header file
#include "pin_def.h"    // Include the pin definition header
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Task functions prototypes
void BlinkTask(void *pvParameters);
void SerialTask(void *pvParameters);


void setup() {
  Serial.begin(115200);
  delay(1000);

  // Configure the status LED pin as an output
  pinMode(STATUS_LED_PIN, OUTPUT);

  Serial.println("Ambilight system started.");
  
  // Create the Blink task
  xTaskCreate(
    BlinkTask,          /* Task function */
    "BlinkTask",        /* Name of the task */
    1000,               /* Stack size in words */
    NULL,               /* Task input parameter */
    1,                  /* Priority of the task */
    NULL);              /* Task handle */

  // Create the Serial task
  xTaskCreate(
    SerialTask,         /* Task function */
    "SerialTask",       /* Name of the task */
    1000,               /* Stack size in words */
    NULL,               /* Task input parameter */
    1,                  /* Priority of the task */
    NULL);              /* Task handle */
  
}



void loop() {

}

void BlinkTask(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    digitalWrite(STATUS_LED_PIN, HIGH);   // Turn the LED on
    vTaskDelay(pdMS_TO_TICKS(1000));      // Wait for one second
    digitalWrite(STATUS_LED_PIN, LOW);    // Turn the LED off
    vTaskDelay(pdMS_TO_TICKS(1000));      // Wait for another second
  }
}


// SerialTask to handle serial communicationvoid SerialTask(void *pvParameters) {
void SerialTask(void *pvParameters) {
  (void) pvParameters;
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

