// Source : http://f-leb.developpez.com/tutoriels/arduino/bus-i2c/

#include "Arduino.h"
#include "DS1621.h"

DS1621::DS1621(uint8_t A0, uint8_t A1, uint8_t A2)
{
    _address = (0x48 | A2 << 2 | A1 << 1 | A0);
}

DS1621::~DS1621()
{

}

void DS1621::begin()
{
    Wire.begin();
    setConfigRegister(0, 0, 0, 0, 1);
}

void DS1621::setConfigRegister(uint8_t THF, uint8_t TLF, uint8_t NVB, uint8_t POL, uint8_t ONESHOT)
{
    Wire.beginTransmission(_address);
    Wire.write(STOP_CONVERT);
    Wire.endTransmission();

    Wire.beginTransmission(_address);
    Wire.write(ACCESS_CONFIG);   // Accès au registre de configuration
    Wire.write((THF << 6 | TLF << 5 | NVB << 4 | POL << 1 | ONESHOT)); // écriture dans le registre de configuration
    Wire.endTransmission();
}

void DS1621::startConversion()
{
    Wire.beginTransmission(_address);
    Wire.write(START_CONVERT);
    Wire.endTransmission();
}

uint8_t DS1621::isAvailable()
{
    uint8_t value = 0;

    Wire.beginTransmission(_address);
    Wire.write(ACCESS_CONFIG);
    Wire.endTransmission(false);  // Condition RESTART
    Wire.requestFrom(_address, 1); // Un octet est requis
    while (Wire.available())
    {
        value = Wire.read() & DONE_MASK;
    }

    return value;
}

float DS1621::readTemperature()
{
    uint8_t temperatureMSB = 0;
    uint8_t temperatureLSB = 0;
    float temperature;

    Wire.beginTransmission(_address);
    Wire.write(READ_TEMPERATURE);
    Wire.endTransmission(false);  // Condition RESTART
    Wire.requestFrom(_address, 2); // Deux octets sont requis
    if (2 <= Wire.available()) {
        temperatureMSB = Wire.read();  // Octet de poids fort
        temperatureLSB = Wire.read();  // Octet de poids faible
    }

    /* Faire les calculs et afficher la température en degrés Celcius */
    temperature = (float) temperatureMSB;
    if (temperatureLSB & 0x80) temperature += 0.5;  // 1/2 °C à prendre en compte
    if (temperatureMSB & 0x80) temperature -= 256;  // Température négative

    return temperature;
}