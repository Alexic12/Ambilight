/**
 * @file main.cpp
 * @brief This file contains the main code for the Ambilight system.
 */

#include <Arduino.h> // Include the Arduino library
#include "serial_comm.h" // Include the SerialComm class header file
#include "led_driver.h"   // Include the LedDriver class header file
#include "pin_def.h"    // Include the pin definition header
#include <freertos/FreeRTOS.h> // Include the FreeRTOS library
#include <freertos/task.h>   // Include the task library

// Task functions prototypes
void BlinkTask(void *pvParameters);
void SerialTask(void *pvParameters);
void LedTask(void *pvParameters);

/**
 * @brief The setup function initializes the system.
 * It configures the serial communication, sets up the status LED pin, and creates the Blink and Serial tasks.
 */

SerialComm serialComm(BAUD_RATE); // Create a SerialComm object
LedDriver ledDriver; // Create a LedDriver object
String currentCommand = "OFF";

void setup() {
  
  // Initialize the serial communication
  serialComm.init();
  ledDriver.init(); // Initialize the LedDriver class
  delay(100);
  serialComm.debugPrint("Debug mode is ON, and system initialization complete.");

  // Configure the status LED pin as an output
  pinMode(STATUS_LED_PIN, OUTPUT);

  // Initialize the LED driver
  
  //Task Example

  //Create the Blink task
  //xTaskCreate(
  //  BlinkTask,          /* Task function */
  //  "BlinkTask",        /* Name of the task */
  //  1000,               /* Stack size in words */
  //  NULL,               /* Task input parameter */
  //  1,                  /* Priority of the task */
  //  NULL);              /* Task handle */
  // Create the Blink task
  // Create the Blink task
  xTaskCreate(BlinkTask, "BlinkTask", 1000, NULL, 2, NULL);

  // Create the Serial task
  xTaskCreate(SerialComm::SerialTask, "SerialTask", 3000, NULL, 1, NULL);

  // Create the LedDriver task
  xTaskCreate(LedDriver::LedTask, "LedTask", 2000, NULL, 2, NULL);

}

/**
 * @brief The loop function is empty as the system is event-driven.
 */
void loop() {

}

/**
 * @brief The BlinkTask function is a FreeRTOS task that toggles the status LED on and off every second.
 * @param pvParameters The task parameters (not used in this case).
 */
void BlinkTask(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    digitalWrite(STATUS_LED_PIN, HIGH);   // Turn the LED on
    vTaskDelay(pdMS_TO_TICKS(1000));      // Wait for one second
    digitalWrite(STATUS_LED_PIN, LOW);    // Turn the LED off
    vTaskDelay(pdMS_TO_TICKS(1000));      // Wait for another second
  }
}



