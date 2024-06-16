# include <Arduino.h>
# include <temprature.h>
# include <LedMatrix.h>

// Joystick pins
# define JPINX          A0
# define JPINY          A1
# define JBUTTON        PE2  

// LED Matrix pins
#define LED_LATCH 11
#define LED_DATA 16
#define LED_CLOCK 15

// setup
TempratureSensor sensor;
JoystickLow js = JoystickLow(JPINX,JPINY,JBUTTON);
// matrix and buffer
LedMatrix ledMatrix(LED_LATCH,LED_DATA,LED_CLOCK);
LedMatrixTextBuffer textBuffer(ledMatrix);
void setup() {
  // always begin serial, who knows
  Serial.begin(9600);
  delay(1000);
  sensor.begin();
  // set resolution to (0b11 or 3)12 bit
  sensor.setResolution(3);
  delay(1000);
  sensor.update();
  js.setDeadzone(25);
  js.begin();
  sensor.switchToContinuousMode();
}

void floatToChar(char *chr, float f ){

  uint8_t tmp = (int) f;
  uint8_t tmp_fl = (f - tmp) *100;
  sprintf (chr, "%d.%02d ", tmp, tmp_fl); //
}

// loop
uint16_t start = millis();
int step = 0;
void loop() {
  float temp = sensor.getTemperature(false);
  char text[6];
  floatToChar(text,temp);
  textBuffer.drawText(text);
  textBuffer.update();
  uint16_t now = millis();
  js.update();
  // if joystick button is pressed text will stop sliding to the left
  if(now-start > 100 && !js.getButton()){
    textBuffer.slideLeft(1);
    step++;
    start = now;
  }
  // update temprature every 3 seconds
  if(step > 30){
    sensor.update();
    Serial.print("Current temprature: ");
    Serial.println(temp);
    step = 0;
  }
}