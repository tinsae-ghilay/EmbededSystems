# ifndef ENUMS_H
# define SENUMS_H


// LED color state
// RED, GREEN, YELLOW and BLINKING if it is blinking
enum ColorState{
    RED,GREEN,YELLOW, BLINK
};

// LED status
// ON - OFF
enum LedState{
    ON,OFF
};

// Button state
// PRESSED when button is pressed,
// RELEASED when button is released
enum btnState{
    PRESSED, RELEASED
};

# endif// ENUMS_H