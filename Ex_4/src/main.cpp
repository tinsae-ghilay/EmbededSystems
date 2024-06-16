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
}

// converts float to char array
void floatToChar(char *chr, float f ){
  // because float was printed as '?' when using sprintf(chr, "%.2f",f)
  // we have to convert decimal and floating point values to uint8_t and append them in sprintf();
  // first the int part of the float.
  uint8_t tmp = (int) f;
  // and the decimal part as integer -> float - the int part multiplied by 100 -> (because 2 nachkommazahlen)
  uint8_t tmp_fl = (f - tmp) *100;
  // and we transfer it to char array
  sprintf (chr, "%d.%02d ", tmp, tmp_fl); 
}

// breaking time stamp 
uint16_t start = millis();
// counter to help us count 3 seconds
int step = 0;

// loop
void loop() {
  // get the saved temprature value
  float temp = sensor.getTemperature(false);
  // convert it to char array, because ledMatrix doesnt accept floats
  char text[6];
  floatToChar(text,temp);
  // draw text
  textBuffer.drawText(text);
  textBuffer.update();
  // current timestamp
  uint16_t now = millis();
  // update joystick to get its status
  js.update();
  // if joystick button is pressed text will stop sliding to the left
  if(now-start > 100 && !js.getButton()){
    textBuffer.slideLeft(1);
    // every 100 millisecond is counted as one
    step++;
    // breaking timestamp
    start = now;
  }
  // update temprature every 3 seconds
  if(step > 30){
    // update sensor to save new temprature value
    sensor.update();
    // printing to sensor
    Serial.print("Current temprature: ");
    Serial.println(temp);
    // 3 seconds have passed, so we reset our counter
    step = 0;
  }
}