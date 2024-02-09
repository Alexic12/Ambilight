/**
 * @file main.cpp
 * @brief This file contains the main code for the Ambilight system.
 */

#include <Arduino.h> 
#include "serial_comm.h" 
#include "led_driver.h"  
#include "pin_def.h"  
#include <freertos/FreeRTOS.h> 
#include <freertos/task.h>   

// Task functions prototypes
void BlinkTask(void *pvParameters);
void SerialTask(void *pvParameters);
void LedTask(void *pvParameters);

/**
 * @brief The setup function initializes the system.
 * It configures the serial communication, sets up the status LED pin, and creates the Blink, Serial tasks and WS2812B Strip task.
 */

SerialComm serialComm(BAUD_RATE); // Create a SerialComm object
LedDriver ledDriver; // Create a LedDriver object
String currentCommand = "OFF"; // Initialize the current command to "OFF" (no animation)  

void setup() {
  
  serialComm.init(); // Initialize the serial communication
  ledDriver.init(); // Initialize the LedDriver class
  serialComm.initMessage(); // Print a message to the serial monitor

  // Configure the status LED pin as an output
  pinMode(STATUS_LED_PIN, OUTPUT);


  ////////////////////////
  //Task Example

  //xTaskCreate(
  //  BlinkTask,          /* Task function */
  //  "BlinkTask",        /* Name of the task */
  //  1000,               /* Stack size in words */
  //  NULL,               /* Task input parameter */
  //  1,                  /* Priority of the task */
  //  NULL);              /* Task handle */
  ////////////////////////
  // Create the Blink task
  //xTaskCreate(BlinkTask, "BlinkTask", 1000, NULL, 2, NULL);

  // Create the Serial task
  xTaskCreate(SerialComm::SerialTask, "SerialTask", 2000, NULL, 1, NULL);

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
  serialComm.debugPrint("BlinkTask started.");
  for (;;) {
    digitalWrite(STATUS_LED_PIN, HIGH);   // Turn the LED on
    vTaskDelay(pdMS_TO_TICKS(200));      // Wait for one second
    digitalWrite(STATUS_LED_PIN, LOW);    // Turn the LED off
    vTaskDelay(pdMS_TO_TICKS(200));      // Wait for another second
  }
}



