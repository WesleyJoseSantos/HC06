/**
 * @file HC06.h
 * @author Wesley José Santos (binary_quantum.com)
 * @brief HC06 Bluetooth Serial Adapter plug-and-play lib
 * @version 0.1
 * @date 2020-04-07
 */

#include "HC06.h"

unsigned long baudRates[] = {
    1200,
    2400,
    4800,
    9600,
    19200,
    38400,
    57600,
    115200,
    230400
};

/**
 * @brief Get HC06 configured baudRate
 * 
 * @return long baudRate
 */
long HC06::getBaudRate(){
    delay(100);
    #ifdef HC06_DEBUG
    HC06_DEBUG.print("Checking baud rate | "); 
    #endif
    for (size_t i = 0; i < 9; i++)
    {
        #ifdef HC06_DEBUG
        HC06_DEBUG.print("#");
        #endif
        this->begin(baudRates[i]);
        this->print("AT");
        delay(1000);
        if(this->available()){
            #ifdef HC06_DEBUG
            HC06_DEBUG.println(" | 100% Baud Rate Detected: "); HC06_DEBUG.println(baudRates[i]);
            #endif
            detectedBaudRate = baudRates[i];
            return(baudRates[i]);
        }
    }
    #ifdef HC06_DEBUG
    HC06_DEBUG.println(" | 100% Baud Rate Error: HC05 doesn't respond.");
    #endif
    return(ERR_TIMEOUT);
}

/**
 * @brief Setup HC06 module sending parameters with AT commands
 * 
 * @param name Name of HC06 acess point
 * @param baudRate BaudRate of HC06
 * @param PIN PIN code to protect HC06
 * @param checkBaudRate Get HC06 configured baudRate before setup
 * @return ErrCode
 */
int HC06::setup(String name = "HC06", String PIN = "1234", unsigned long baudRate = 9600UL, bool checkBaudRate = true){
    #ifdef HC06_DEBUG
    HC06_DEBUG.println("Starting setup of HC06.");
    #endif
    if(checkBaudRate){
        getBaudRate();
        this->begin(detectedBaudRate);
    }else{
        this->begin(baudRates[baudRate-1]);
    }
    int err_code = setBaud(baudRate);
    if(err_code) return(ERR_SETUP);
    if(checkBaudRate)
        this->begin(baudRate);
    err_code = setName(name);
    if(err_code) return(ERR_SETUP);
    err_code = setPIN(PIN);
    if(err_code) return(ERR_SETUP);
    #ifdef HC06_DEBUG
    if(err_code == 0)
        HC06_DEBUG.println("HC06 Setup completed without any errors!");
    else
        HC06_DEBUG.println("HC06 Setup error!");
    #endif
    return(err_code);
}

/**
 * @brief Configure new baudRate to HC06
 * 
 * @param baudRate new baudRate
 * @return int ErrCode
 */
int HC06::setBaud(unsigned long baudRate){
    String baud =  "4";
    for (size_t i = 0; i < 9; i++)
    {
        if(baudRate == baudRates[i]){
            i += 1;
            String(i);
            break;
        }
    }    
    return sendMessage("BAUD", baud);
}

/**
 * @brief Configure new name to HC06 acess point.
 * @note To complete this configuration HC06 requires a hard reset
 * @param name 
 * @return int ErrCode
 */
int HC06::setName(String name){
    return sendMessage("NAME", name);
}

/**
 * @brief Configure new PIN code to HC06
 * 
 * @param newPIN new PIN code
 * @return int ErrCode
 */
int HC06::setPIN(String newPIN){
    return sendMessage("PIN", newPIN);
}

/**
 * @brief Checks HC06 connection
 * 
 * @return true if connection is ok
 * @return false otherwise
 */
bool HC06::checkConnection(){
    if(connected){
        return(true);
    } 
    #ifdef HC06_DEBUG
    HC06_DEBUG.print("Checking connection... ");
    #endif
    this->print("AT");
    delay(1000);
    if (this->available() && this->readString() == "OK")
    {
        #ifdef HC06_DEBUG
        HC06_DEBUG.println("OK!");
        #endif
        connected = true;
        return(true);
    }
    #ifdef HC06_DEBUG
    HC06_DEBUG.println("Error!");
    #endif
    return(false);
}

/**
 * @brief Send configuration message to HC06 module
 * 
 * @param message configuration message
 * @param data configuration parameter
 * @return int ErrCode
 */
int HC06::sendMessage(String message, String data){
    #ifdef HC06_DEBUG
    HC06_DEBUG.print("Setting "); HC06_DEBUG.print(message); HC06_DEBUG.print(" to "); HC06_DEBUG.println(data); 
    #endif
    if(checkConnection()){
        this->print("AT+");
        this->print(message);
        this->print(data);
        delay(1000);
        if(this->available()){
            #ifdef HC06_DEBUG
            HC06_DEBUG.println(this->readString());
            #endif
            return(ERR_OK);
        }
    }
    #ifdef HC06_DEBUG
    HC06_DEBUG.println("Failed.");
    #endif
    return(ERR_TIMEOUT);
}