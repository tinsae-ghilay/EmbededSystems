/*
* by Tinsae Ghilay on Jun 2, 2024
* for Computer structures and Embeded Systems 
*/

# ifndef DISPLAY_H
# define DISPLAY_H

# include <Arduino.h>

class Display{
    private:

    int x = 0, lPin,dPin,cPin;

    byte buffer[8];

    public:
    Display(int latchPin, int dataPin, int clockPin);

    void setProximity(int duration);
    void start();
    void loop();
    void update();
    void clear();
    void on();


};

# endif//DISPLAY_H