

# include "temprature.h"

//Initialisiert den Sensor.
void TempratureSensor::begin(){}
// Schaltet den normalen kontinuierlichen Betriebmodus ein.
void TempratureSensor::switchToContinuousMode(){}
// Schaltet den One-Shot Betriebsmodus ein.
void TempratureSensor::switchToOneShotMode(){}
// Erlaubt das Einstellen der Messgenauigkeit.
void TempratureSensor::setResolution(uint8_t res){}
// Liest die aktuelle Temperatur aus und speichert diese zwischen.
void TempratureSensor::update(){}
// Gibt entweder (immediate == false) den von update() zwischengespeicherten Wert zurück, 
// oder liest die aktuelle Temperatur aus (immediate == true, analog zum Joystick-Gerätetreiber)
float TempratureSensor::getTemperature(bool immediate = false){} 
