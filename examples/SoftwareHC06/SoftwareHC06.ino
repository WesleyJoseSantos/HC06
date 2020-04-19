/**
 * @file MinimalHC06Setup.ino
 * @author Wesley José Santos (binary_quantum.com)
 * @brief Complete setup of HC06 using SoftwareSerial library of Arduino. Plug-and-Play!
 * @version 0.1
 * @date 2020-04-07
 */

#define HC06_DEBUG Serial           //Macro to enable and define a Serial to be used for HC06 debug messages
#define HC06_SOFTWARE               //Macro to enable use of SoftwareSerial HC06 class
#include "HC06.h"

HC06 hc06 = HC06(A1, A2);           //Create HC06 instance using a SoftareSerial at A1 and A2 Arduino pins

#define HC06_NAME "HC06Example"     //HC06 custom acess point name
#define HC06_PIN "1234"             //HC06 custom pin code
#define HC06_BAUD 9600UL            //HC06 custom baud rate

void setup() {
  // put your setup code here, to run once:
  hc06.setup(HC06_NAME, HC06_PIN, HC06_BAUD);      //Complete setup of HC06 with specific bluetooth parameters.
                                                   //!Some parameters require a Hard Reset of hc06 after setup 
                                                   //!to be changed!
}                                                  

void loop() {
  // put your main code here, to run repeatedly:
  hc06.println("Hello World!");     //Print Hello World message to HC06 adapter
  delay(1000);                      //Wait for a second
}