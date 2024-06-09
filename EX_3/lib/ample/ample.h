
#ifndef AMPLE_H
#define AMPLE_H
// pins
# define RGB_LED_PIN 	A4
# define BUTTON_PIN     PE2
# include <Arduino.h>
# include <Adafruit_NeoPixel.h>
# include <sensor.h>
# include <enums.h>


class Ample
{
    private:
    ColorState cState;
    LedState lState;
    btnState bState = RELEASED;
    bool nightMode = false, toRed = false, emergency = false, jWalking = false;
    bool readBtn();
    Adafruit_NeoPixel lamp = Adafruit_NeoPixel(1, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);
    Sensor sensor = Sensor(8,4);
    void blockWalkers();

    public:
    void start();
    void loop();
    bool btnPressed();
    void checkBrightness();
    void red();
    void green();
    void yellow();
    void on(uint8_t red, uint8_t green, uint8_t blue);
    void off();
    void blink();
    void allowEmergency();
    void nightRun();

};
#endif// AMPLE_H