//
// Created by tgk on 5/24/24.
//

#include "JoystickHigh.h"

JoystickHigh::JoystickHigh(int pinX, int pinY, int pinButton)
{}

// Initialisiert den Gerätetreiber. Wird einmalig zu Beginn des Mikrocontroller-Programms ausgeführt.
void JoystickHigh::begin()
{}

// Liest die aktuellen Werte der Joystick-Achsen und des Buttons aus und speichert diese zwischen.
void JoystickHigh::update()
{}

// Gibt die aktuelle Position der x-Achse zurück.
// Der mögliche Wertebereich soll von -512 (links) über 0 (Ruheposition) bis 512 (rechts) gehen.
int16_t JoystickHigh::getPosX(bool immediate)
{}

// Gibt die aktuelle Position der y-Achse zurück.
// Der mögliche Wertebereich soll von -512 (links) über 0 (Ruheposition) bis 512 (rechts) gehen.
int16_t JoystickHigh::getPosY(bool immediate)
{}

// Gibt den aktuellen Status des Buttons zurück. Rückgabewert ist true, wenn der Button gerade gedrückt ist, ansonsten false
bool JoystickHigh::getButton(bool immediate)
{}

// Erlaubt es, die Deadzone des Joysticks einzustellen.
void JoystickHigh::setDeadzone(int16_t deadzone)
{}