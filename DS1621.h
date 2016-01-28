// Source : http://f-leb.developpez.com/tutoriels/arduino/bus-i2c/

#ifndef DS1621_h
#define DS1621_h

#include "Arduino.h"
#include "Wire.h"

#define DONE_MASK   0x80   // Masque pour bit DONE

/* Commandes du DS1621 */
#define READ_TEMPERATURE  0xAA
#define ACCESS_CONFIG     0xAC
#define START_CONVERT     0xEE
#define STOP_CONVERT      0x22

class DS1621
{
public:
    DS1621(uint8_t A0, uint8_t A1, uint8_t A2);
    ~DS1621();

    void begin();
    void setConfigRegister(uint8_t THF, uint8_t TLF, uint8_t NVB, uint8_t POL, uint8_t ONESHOT);
    void startConversion();
    uint8_t isAvailable();
    float readTemperature();
private:
    uint8_t _address;
};


#endif