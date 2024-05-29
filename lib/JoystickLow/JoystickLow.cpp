//
// Created by tgk on 5/24/24.
//

#include <JoystickLow.h>
#include <avr/io.h>
#include <stdint.h>

JoystickLow::JoystickLow(uint16_t x, uint16_t y, uint16_t b)
{
    this->btnPin = b;
    this->xPin = x;
    this->yPin = y;
    
    DDRD &= ~(1 << btnPin);
    DDRC = DDRC & 0xFB;
}

// Initialisiert den Gerätetreiber. Wird einmalig zu Beginn des Mikrocontroller-Programms ausgeführt.
void JoystickLow::begin()
{

    DDRE = DDRE & ~(1 << PE2); // PE2 als Digitaleingang konfigurieren
	PORTE = PORTE & ~(1 << PE2); // Pullup-Widerstand für PE2 ausschalten

    this->btnPressed = false;
    Serial.begin(115200);
}

// Liest die aktuellen Werte der Joystick-Achsen und des Buttons aus und speichert diese zwischen.
void JoystickLow::update()
{
    this->pos_x = this->getPosX(true);
    this->pos_y = this->getPosY(true);
    this->btnPressed = this->getButton(true);
}

// Gibt die aktuelle Position der x-Achse zurück.
// Der mögliche Wertebereich soll von -512 (links) über 0 (Ruheposition) bis 512 (rechts) gehen.
int16_t JoystickLow::getPosX(bool immediate)
{
    return immediate? this->adjust(this->xPin):this->pos_x;
}

// Gibt die aktuelle Position der y-Achse zurück.
// Der mögliche Wertebereich soll von -512 (Unten) über 0 (Ruheposition) bis 512 (oben) gehen.
int16_t JoystickLow::getPosY(bool immediate)
{
    return immediate? this->adjust(this->yPin):this->pos_y;
}

// Gibt den aktuellen Status des Buttons zurück. 
// Rückgabewert ist true, wenn der Button gerade gedrückt ist, ansonsten false
bool JoystickLow::getButton(bool immediate)
{
    return immediate? this->readBtn(): this->btnPressed;
}

// Erlaubt es, die Deadzone des Joysticks einzustellen.
void JoystickLow::setDeadzone(int16_t deadzone)
{
    this->dead_zone = deadzone;
}

int16_t JoystickLow::adjust(int16_t pin){
    int value = this->readPin(pin);
    value = this->map(value, 0, 1023, -512, 512);
    return (this->absVal(value) > this->dead_zone)? value: 0;
}

void JoystickLow::getDirection()
{
    Serial.print("Mous position = ");
    Serial.print((this->pos_x < 0)?" LEFT - ":(this->pos_x == 0)?" CENTRE - ":" RIGNT - ");
    Serial.print((this->pos_y< 0)? "DOWN":(this->pos_y == 0)? "CENTRE":"UP");
    Serial.print("\n");
}
int16_t JoystickLow::absVal(int16_t a)
{
    return (a < 0)? a*-1: a;
}

bool JoystickLow::readBtn()
{
    return PINE & (1 << PE2);
}

int16_t JoystickLow::readPin(uint8_t pin) 
{
    	// Konfiguriere die Betriebsspannung als Referenzspannung, und wähle Analogeingang ADC5 aus
	ADMUX = (1 << REFS0) | pin;

	// Schalte den Analog/Digital-Wandler ein, und setzt einen passenden Prescaler-Wert
	// Analog/Digital-Wandler-Frequenz = CPU-Frequenz / Prescaler-Wert
	// Die Wandler-Frequenz sollte zwischen 50kHz und 200kHz liegen
	// In unserem Fall: 16MHz / 128 = 125kHz
	ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);

	// Starte den Umwandlungsprozess zum Auslesen des Helligkeitssensors
	ADCSRA = ADCSRA | (1 << ADSC);

	// Solange das ADSC-Bit im ADCSRA Register 1 ist, ist der Umwandlungsprozess noch nicht abgeschlossen
	// Daher warten wir, bis dieses Bit 0 ist
	while (ADCSRA & (1 << ADSC));

    	// Lese das Umwandlungsergebnis aus
	int low = ADCL; // Zuerst immer ADCL auslesen!
	int high = ADCH; // Erst dann ADCH auslesen!
	int value = (high << 8) | low; // Das endgültige Ergebnis zusammenbauen
	return value;

    
}

long JoystickLow::map(long x, long in_min, long in_max, long out_min, long out_max) 
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void JoystickLow::loop()
{
    this->update();
    Serial.print(" Pos x = ");
    Serial.print(this->getPosX());
    Serial.print(" and Pos y = ");
    Serial.print(this->getPosY());
    Serial.print(" Button Pressed? ");
    Serial.print(this->getButton());
    Serial.print("\n");
    this->getDirection();
}