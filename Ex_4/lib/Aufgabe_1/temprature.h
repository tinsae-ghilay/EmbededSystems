
# ifndef TEMPRATURE_H
# define TEMPRATURE_H
# include <Arduino.h>

class TempratureSensor{


    public:

    void begin(); //Initialisiert den Sensor.
    void switchToContinuousMode();// Schaltet den normalen kontinuierlichen Betriebmodus ein.
    void switchToOneShotMode(); // Schaltet den One-Shot Betriebsmodus ein.
    void setResolution(uint8_t res); // Erlaubt das Einstellen der Messgenauigkeit.
    void update(); // Liest die aktuelle Temperatur aus und speichert diese zwischen.
    float getTemperature(bool immediate = false); // Gibt entweder (immediate == false) den von update() zwischengespeicherten Wert zurück, oder liest die aktuelle Temperatur aus (immediate == true, analog zum Joystick-Gerätetreiber auf dem ersten Übungszettel)

};

#endif //TEMPRATURE_H