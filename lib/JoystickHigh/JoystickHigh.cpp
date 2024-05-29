//
// Created by tgk on 5/24/24.
//

#include "JoystickHigh.h"

JoystickHigh::JoystickHigh(uint16_t x, uint16_t y, uint16_t b)
{
    this->btnPin = b;
    this->xPin = x;
    this->yPin = y;

	this->btnPressed = false;
	pinMode (this->btnPin, INPUT);
	//pinMode (this->xPin, INPUT_PULLUP); // Joystick X axis
	//pinMode (this->yPin, INPUT_PULLUP); // Joystick Y axis
}

// Initialisiert den Gerätetreiber. Wird einmalig zu Beginn des Mikrocontroller-Programms ausgeführt.
void JoystickHigh::begin()
{
    pinMode(this->btnPin, INPUT);
    this->btnPressed = false;
    Serial.begin(9600);
}

// Liest die aktuellen Werte der Joystick-Achsen und des Buttons aus und speichert diese zwischen.
void JoystickHigh::update()
{
    this->pos_x = this->getPosX(true);
    this->pos_y = this->getPosY(true);
    btnPressed = this->getButton(true);
}

// Gibt die aktuelle Position der x-Achse zurück.
// Der mögliche Wertebereich soll von -512 (links) über 0 (Ruheposition) bis 512 (rechts) gehen.
int16_t JoystickHigh::getPosX(bool immediate)
{
    return immediate? this->adjust(xPin):this->pos_x;
}

// Gibt die aktuelle Position der y-Achse zurück.
// Der mögliche Wertebereich soll von -512 (Unten) über 0 (Ruheposition) bis 512 (oben) gehen.
int16_t JoystickHigh::getPosY(bool immediate)
{
    return immediate? this->adjust(yPin):this->pos_y;
}

// Gibt den aktuellen Status des Buttons zurück. 
// Rückgabewert ist true, wenn der Button gerade gedrückt ist, ansonsten false
bool JoystickHigh::getButton(bool immediate)
{
    return immediate? digitalRead(this->btnPin): PINE & 0x04;
}

// Erlaubt es, die Deadzone des Joysticks einzustellen.
void JoystickHigh::setDeadzone(int16_t deadzone)
{
    this->dead_zone = deadzone;
}

int16_t JoystickHigh::adjust(int16_t pin){
    int value = analogRead(pin);
    value = map(value, 0, 1023, -512, 512);
    return (abs(value) > this->dead_zone)? value: 0;
}

void JoystickHigh::getDirection()
{
    Serial.print("Mous position = ");
    Serial.print((pos_x < 0)?" LEFT - ":(pos_x == 0)?" CENTRE - ":" RIGNT - ");
    Serial.print((pos_y< 0)? "DOWN":(pos_y == 0)? "CENTRE":"UP");
    Serial.print("\n");
}

void JoystickHigh::loop()
{
    this->update();
    Serial.print(" Pos x = ");
    Serial.print(this->getPosX());
    Serial.print(" and Pos y = ");
    Serial.print(this->getPosY());
    Serial.print(" Button Pressed? ");
    Serial.print(this->getButton()?"Yes":"No");
    Serial.print("\n");
    this->getDirection();
}
