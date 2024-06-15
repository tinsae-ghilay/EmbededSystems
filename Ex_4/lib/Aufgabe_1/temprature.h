
# ifndef TEMPRATURE_H
# define TEMPRATURE_H
# include <Arduino.h>
# include <Wire.h>
# include <bitoperations.h>


#define REG_AMBIENT         0
#define REG_CONFIG 	        1
#define I2C  		    0x48

class TempratureSensor{

    private:
    bool oneShot = false;
    float temprature = 0.0;
    //uint8_t readU8(uint8_t reg);
    uint16_t read(int reg);
    void write(uint8_t reg, uint8_t val);
    void setMode(bool continous);
    uint8_t i2c;

    public:

    void begin(); //Initialisiert den Sensor.
    void switchToContinuousMode();// Schaltet den normalen kontinuierlichen Betriebmodus ein.
    void switchToOneShotMode(); // Schaltet den One-Shot Betriebsmodus ein.
    void setResolution(uint8_t res); // Erlaubt das Einstellen der Messgenauigkeit.
    void update(); // Liest die aktuelle Temperatur aus und speichert diese zwischen.
    float getTemperature(bool immediate = false); // Gibt entweder (immediate == false) den von update() zwischengespeicherten Wert zurück, oder liest die aktuelle Temperatur aus (immediate == true, analog zum Joystick-Gerätetreiber auf dem ersten Übungszettel)

};

#endif //TEMPRATURE_H