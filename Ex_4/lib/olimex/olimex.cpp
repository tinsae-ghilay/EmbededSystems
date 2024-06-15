/*-------------------------------------------------------------------------
  Arduino library for controlling a Temperature Sensor.

  Olimex_TCN75 (int _Address) - initializes the class with the i2c address on which the sensor is attached as a parameter
  int RawData () - the value read by the sensor
  float Temperature () - the calculated temperature based on the value read by the sensor
  -------------------------------------------------------------------------*/

#include "olimex.h"

Olimex_TCN75::Olimex_TCN75 (int _Address)
{
	Wire.begin ();
	Address = _Address;
}

int Olimex_TCN75::RawData ()
{
	int Data;
	Wire.beginTransmission(Address);// Start transmission
	Wire.write(0);					// move your register pointer back to 00h
	Wire.endTransmission();			// Stop transmission
	Wire.requestFrom(Address, 2);	// Send me the contents of your first two bytes
	Data = Wire.read();				// first received byte stored here
	Data = (Data<<8) | Wire.read();	// second received byte stored here
	return Data;			// convert received bytes into float value
}

float Olimex_TCN75::Temperature()
{
	int Data;
	Data = RawData ();
	Data = Data >> 7;
	return (float)Data / 2;
}
