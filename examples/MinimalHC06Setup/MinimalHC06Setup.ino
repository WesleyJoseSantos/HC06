/**
 * @file MinimalHC06Setup.ino
 * @author Wesley José Santos (binary_quantum.com)
 * @brief Minimal setup of HC06 using default Serial port of Arduino. Plug-and-Play!
 * @version 0.1
 * @date 2020-04-07
 */

#include "HC06.h"

HC06 hc06 = HC06(Serial);     //Create HC06 instance using the default HardwareSerial of Arduino 

void setup() {
  // put your setup code here, to run once:
  hc06.setup();      //Complete setup of HC06 with default bluetooth parameters.
}

void loop() {
  // put your main code here, to run repeatedly:
  hc06.println("Hello World!");     //Print Hello World message to HC06 adapter
  delay(1000);                      //Wait for a second
}