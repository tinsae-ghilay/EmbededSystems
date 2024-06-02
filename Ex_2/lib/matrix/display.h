/*
* by Tinsae Ghilay on Jun 2, 2024
* for Computer structures and Embeded Systems 
*/

# ifndef DISPLAY_H
# define DISPLAY_H

# include <LedMatrix.h>
# include <Arduino.h>

class Display{
    private:

    int x = 0;
    LedMatrix matrix = LedMatrix(11,16,15);

    public:

    void setProximity(int duration);
    void start();
    void loop();

};

# endif//DISPLAY_H