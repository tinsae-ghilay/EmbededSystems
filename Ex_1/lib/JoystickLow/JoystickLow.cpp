//
// Created by tgk on 5/24/24.
// teted on Olimex eduArdu atmega32u4 arduino board.
//

#include <JoystickLow.h>
#include <avr/io.h>
# include <Arduino.h>
#include <bitoperations.h>


// constructor
JoystickLow::JoystickLow(uint16_t x, uint16_t y, uint16_t b)
{
    this->btnPin = b;
    this->xPin = x;
    this->yPin = y;
}

// Initialisiert den Gerätetreiber. Wird einmalig zu Beginn des Mikrocontroller-Programms ausgeführt.
void JoystickLow::begin()
{
    // we dont need to explicitely set pins as input here
    // because buttons are set as input by default.

    // check Serial, if not running start it
    if(!Serial){
        Serial.begin(9600);
    }

    // button is not pressed in the begining
    this->btnPressed = false;
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
    return immediate? this->adjust(this->xPin) : this->pos_x;
}

// Gibt die aktuelle Position der y-Achse zurück.
// Der mögliche Wertebereich soll von -512 (Unten) über 0 (Ruheposition) bis 512 (oben) gehen.
int16_t JoystickLow::getPosY(bool immediate)
{
    return immediate? this->adjust(this->yPin) : this->pos_y;
}

// Gibt den aktuellen Status des Buttons zurück. 
// Rückgabewert ist true, wenn der Button gerade gedrückt ist, ansonsten false
bool JoystickLow::getButton(bool immediate)
{
    return immediate? this->readBtn() : this->btnPressed;
}

// Erlaubt es, die Deadzone des Joysticks einzustellen.
void JoystickLow::setDeadzone(int16_t deadzone)
{
    this->dead_zone = deadzone;
}
// adjust read value to be between -512 and 512 
// using map()
// specification :
//                Der mögliche Wertebereich soll von -512 (links) über 0 (Ruheposition) bis 512 (rechts) gehen.
int16_t JoystickLow::adjust(int16_t pin){
    int value = this->readPin(pin);
    value = this->map(value, 0, 1023, -512, 512);
    return (this->absVal(value) > this->dead_zone)? value : 0;
}

// get direction where Joystic is pointing.
// and print it to debug console
void JoystickLow::getDirection()
{
    Serial.print("Direction = ");
    // x axis left centre or right?
    Serial.print((pos_x < 0)?" LEFT - ":(pos_x == 0)?" CENTRE - ":" RIGNT - ");
    // y axis Down centre or up?
    Serial.print((pos_y< 0)? "DOWN":(pos_y == 0)? "CENTRE":"UP");
    Serial.print("\n");
}


// retuns absolut value of a number.
int16_t JoystickLow::absVal(int16_t a)
{
    return (a < 0)? a*(-1): a;
}

// reads button pressed or not
// using is bit set macro, declared in bitoperations
bool JoystickLow::readBtn()
{
    return IBS(PINE,btnPin);
}

// maped pins  source gitHub
int8_t  pins[] = {7/*A0*/,6/*A1*/,5/*A2*/,4/*A3*/,1/*A4*/,0/*A5*/
        ,8/*A6*/,10/*A7*/,11/*A8*/,12/*A9*/,13/*A10*/,9/*A11*/};

// reads joystick pin
int16_t JoystickLow::readPin(uint8_t pin) 
{
    // the ADC is enabled by seting the ADC enable bit, ADEN in ADCSRA (source Sakai Datasheet_AVR-ATmega32U4.pdf, page 299).
    SB(ADCSRA, ADEN);
    // select voltage reference  (PDF page 313) try an error :D
    // if I set it to REFS1 x and y positions come at 190 and 150 respectively, 
    // too big for a dead zone, so REFS0 it is.
    // also getting channel from pin, source -- arduino forum "reading ADC register on Leonardo..."
    // and select that analog channel as input
    // _SB(POSITION) is a MACRO in bitoperations.
    ADMUX = _SB(REFS0) | pins[pin];//analogPinToChannel(pin);

    // start conversion i.e set ADSC bit to ADCSRA
    SB(ADCSRA, ADSC);

    // wait for conversion to finish
	while IBS(ADCSRA,ADSC);

    // interrupt when done ADIF enable interrupt when done (PDF page 316)
    SB(ADCSRA,ADIF);
    // return raw ADC value 0-1023;
	return ADC; 
}

// map  from Adrian T.P.
long JoystickLow::map(long x, long in_min, long in_max, long out_min, long out_max) 
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


// loops function prints position of joystic and button status to debug consol
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
