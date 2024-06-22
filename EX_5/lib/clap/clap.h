

# ifndef CLAP_H
# define CLAP_H

# include <Arduino.h>

enum  clap{NONE, DOUBLE, TRIPPLE};

class ClapDetection{

    private: 
    uint16_t threshold;
    uint8_t cl_count = 0, mic;
    clap claps = NONE;
    public:
    
    void setup(uint8_t mic, uint16_t threshold);
    // one clap turns led off
    // two claps turn led on and off
    // three claps Blink LED and of
    void update();

    clap getState();
};

# endif // CLAP