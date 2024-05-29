//
// Created by tgk on 5/24/24.
//

#ifndef JOYSTICKLOW_H
#define JOYSTICKLOW_H

#include <Arduino.h>
#include "bitoperations.h"
#include <avr/io.h>

class JoystickLow {

private:
    bool btnPressed;
    int16_t pos_x, pos_y, dead_zone;
    int16_t xPin, yPin, btnPin;
    int16_t cnt = 0;
    // private functions
    bool readBtn(); 
    int16_t readPin(uint8_t pin);
    long map(long x, long in_min, long in_max, long out_min, long out_max);
    int16_t adjust(int16_t pos);

public:
    JoystickLow(uint16_t x, uint16_t y, uint16_t b);

    // Initialisiert den Gerätetreiber. Wird einmalig zu Beginn des Mikrocontroller-Programms ausgeführt.
    void begin();

    // Liest die aktuellen Werte der Joystick-Achsen und des Buttons aus und speichert diese zwischen.
    void update();

    // Gibt die aktuelle Position der x-Achse zurück.
    // Der mögliche Wertebereich soll von -512 (links) über 0 (Ruheposition) bis 512 (rechts) gehen.
    int16_t getPosX(bool immediate = false);

    // Gibt die aktuelle Position der y-Achse zurück.
    // Der mögliche Wertebereich soll von -512 (links) über 0 (Ruheposition) bis 512 (rechts) gehen.
    int16_t getPosY(bool immediate = false);

    // Gibt den aktuellen Status des Buttons zurück. Rückgabewert ist true, wenn der Button gerade gedrückt ist, ansonsten false
    bool getButton(bool immediate = false);

    // Erlaubt es, die Deadzone des Joysticks einzustellen.
    void setDeadzone(int16_t deadzone);

    void getDirection();

    int16_t absVal(int16_t a);
    void loop();
};


#endif //JOYSTICKLOW_H
