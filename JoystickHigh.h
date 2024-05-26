//
// Created by tgk on 5/24/24.
//

#ifndef JOYSTICKHIGH_H
#define JOYSTICKHIGH_H

#include <cstdint>

class JoystickHigh {

private:
    bool button;
    int16_t pos_x;
    int16_t pos_y;

public:
    JoystickHigh(int pinX, int pinY, int pinButton);

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
};


#endif //JOYSTICKHIGH_H
