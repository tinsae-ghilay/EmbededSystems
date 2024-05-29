# include <Arduino.h>
# include <avr/io.h>


void setup()
{
  Serial.begin(1000000);
}

void loop()
{
  static uint32_t startTime;
  int val = analogRead(A0);
  //int val = analogReadBlocking(A0);

  if (val >= 0)
  {
    Serial.print(micros() - startTime);
    Serial.print(F("us, val = "));
    Serial.println(val);
    Serial.flush();
    startTime = micros();
  }
}

#include <wiring_private.h>

uint8_t analog_reference = DEFAULT;

void analogReference(uint8_t mode)
{
  // can't actually set the register here because the default setting
  // will connect AVCC and the AREF pin, which would cause a short if
  // there's something connected to AREF.
  analog_reference = mode;
}

int analogReadBlocking(uint8_t pin)
{
  uint8_t low, high;

#if defined(analogPinToChannel)
#if defined(__AVR_ATmega32U4__)
  if (pin >= 18) pin -= 18;  // allow for channel or pin numbers
#endif
  pin = analogPinToChannel(pin);
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  if (pin >= 54) pin -= 54;  // allow for channel or pin numbers
#elif defined(__AVR_ATmega32U4__)
  if (pin >= 18) pin -= 18;      // allow for channel or pin numbers
#elif defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
  if (pin >= 24) pin -= 24;      // allow for channel or pin numbers
#else
  if (pin >= 14) pin -= 14;      // allow for channel or pin numbers
#endif

#if defined(ADCSRB) && defined(MUX5)
  // the MUX5 bit of ADCSRB selects whether we're reading from channels
  // 0 to 7 (MUX5 low) or 8 to 15 (MUX5 high).
  ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((pin >> 3) & 0x01) << MUX5);
#endif

  // set the analog reference (high two bits of ADMUX) and select the
  // channel (low 4 bits).  this also sets ADLAR (left-adjust result)
  // to 0 (the default).
#if defined(ADMUX)
#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  ADMUX = (analog_reference << 4) | (pin & 0x07);
#else
  ADMUX = (analog_reference << 6) | (pin & 0x07);
#endif
#endif

  // without a delay, we seem to read from the wrong channel
  //delay(1);

#if defined(ADCSRA) && defined(ADCL)
  // start the conversion
  sbi(ADCSRA, ADSC);

  // ADSC is cleared when the conversion finishes
  while (bit_is_set(ADCSRA, ADSC))
    ;

  // we have to read ADCL first; doing so locks both ADCL
  // and ADCH until ADCH is read.  reading ADCL second would
  // cause the results of each conversion to be discarded,
  // as ADCL and ADCH would be locked when it completed.
  low = ADCL;
  high = ADCH;
#else
  // we dont have an ADC, return 0
  low = 0;
  high = 0;
#endif

  // combine the two bytes
  return (high << 8) | low;
}


/*
Non-blocking analogRead
Returns
  < 0 if reading is not complete
  0..1023 if reading is complete
*/
int16_t analogRead(uint8_t pin)
{
  enum class States
  {
    Idle,
    InProgress,
    Complete,
  };

  static States state = States::Idle;
  static uint32_t startTime;


  //Serial.println("Local non-blocking analogRead");

  uint8_t low, high;
  int retVal = 0xFFFF;


  switch (state)
  {
    case States::Idle:
      startTime = micros();
#if defined(analogPinToChannel)
#if defined(__AVR_ATmega32U4__)
      if (pin >= 18) pin -= 18;  // allow for channel or pin numbers
#endif
      pin = analogPinToChannel(pin);
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
      if (pin >= 54) pin -= 54;  // allow for channel or pin numbers
#elif defined(__AVR_ATmega32U4__)
      if (pin >= 18) pin -= 18;  // allow for channel or pin numbers
#elif defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
      if (pin >= 24) pin -= 24;  // allow for channel or pin numbers
#else
      if (pin >= 14) pin -= 14;  // allow for channel or pin numbers
#endif

#if defined(ADCSRB) && defined(MUX5)
      // the MUX5 bit of ADCSRB selects whether we're reading from channels
      // 0 to 7 (MUX5 low) or 8 to 15 (MUX5 high).
      ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((pin >> 3) & 0x01) << MUX5);
#endif
      // set the analog reference (high two bits of ADMUX) and select the
      // channel (low 4 bits).  this also sets ADLAR (left-adjust result)
      // to 0 (the default).
#if defined(ADMUX)
#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
      ADMUX = (analog_reference << 4) | (pin & 0x07);
#else
      ADMUX = (analog_reference << 6) | (pin & 0x07);
#endif
#endif
#if defined(ADCSRA) && defined(ADCL)
      // start the conversion
      sbi(ADCSRA, ADSC);
#endif
      //Serial.print(F("Idle to InProgress took "));
      //Serial.println(micros() - startTime);
      state = States::InProgress;
      retVal = 0xFFFE;
      // without a delay, we seem to read from the wrong channel
      //delay(1);  break;
      break;
    case States::InProgress:
      // ADSC is cleared when the conversion finishes
#if defined(ADCSRA) && defined(ADCL)
      if (bit_is_set(ADCSRA, ADSC))
      {
        retVal = 0xFFFE;
      }
      else
      {
        //Serial.print(F("Idle to Complete took "));
        //Serial.println(micros() - startTime);
        state = States::Complete;
      }
#else
      state = States::Complete;
#endif
      break;
    case States::Complete:
#if defined(ADCSRA) && defined(ADCL)
      low = ADCL;
      high = ADCH;
#else
      low = 0;
      high = 0;
#endif
      // combine the two bytes
      retVal = (high << 8) | low;
      //Serial.println(F("..switching to Idle"));
      state = States::Idle;
      break;
  }

  return retVal;
}