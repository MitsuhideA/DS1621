#include <DS1621.h>

// Niveau de tension de A0, A1 et A2.
DS1621 temperatureSensor(1, 1, 1);

void setup()
{
    Serial.begin(38400);
    temperatureSensor.begin();
}

void loop()
{
    // Commence une conversion
    temperatureSensor.startConversion();
    
    // Tant que la conversion n'est pas finie
    while (temperatureSensor.isAvailable());

    // Affiche la température
    Serial.println(temperatureSensor.readTemperature());

    delay(5000);
}