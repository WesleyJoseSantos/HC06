/**
 * @file HC06.h
 * @author Wesley José Santos (binary_quantum.com)
 * @brief HC06 Bluetooth Serial Adapter plug-and-play lib
 * @version 0.1
 * @date 2020-04-07
 */

#ifndef __HC06__H__
#define __HC06__H__

#include <Arduino.h>

/**
 * @brief Error Codes of HC06 methods
 * 
 */
enum ErrCode
{
    ERR_OK=0,       //No error
    ERR_TIMEOUT,    //Time out when wait response
    ERR_SETUP,      //Fail on general setup
};

#ifdef HC06_SOFTWARE
#include <SoftwareSerial.h>
class HC06: public SoftwareSerial
#else
class HC06: public HardwareSerial
#endif
{
private:
    long detectedBaudRate;
    int sendMessage(String message, String data);
    bool connected;
public:
    HC06();
    #ifdef HC06_SOFTWARE
    HC06(SoftwareSerial serialInterface): SoftwareSerial(serialInterface){};
    HC06(uint8_t pinRx, uint8_t pinTx, bool inverseLogic = false)
        : SoftwareSerial(pinRx, pinTx, inverseLogic){};
    #else
    HC06(HardwareSerial serialInterface): HardwareSerial(serialInterface){};
    #endif
    long getBaudRate();
    int setup(
        String name = "HC06", 
        String PIN = "1234", 
        unsigned long baudRate = 9600UL, 
        bool checkBaudRate = true
    );
    int setBaud(unsigned long baudRate);
    int setName(String newName);
    int setPIN(String newPIN);
    bool checkConnection();
};

#endif  //!__HC05__H__