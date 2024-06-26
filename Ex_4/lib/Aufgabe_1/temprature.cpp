

# include "temprature.h"

// Private functions
// reads value from a given register
uint16_t TempratureSensor::read(int reg)
{
	uint16_t data;
    // Start transmission
	Wire.beginTransmission(I2C);
	// move your register pointer back to reg
	Wire.write(REG_AMBIENT);
	// stop transmission
	Wire.endTransmission();
	// get first two bits
	Wire.requestFrom(I2C, 2);
	// first recieved byte
	data = Wire.read();
	// second received byte 
	data = (data << 8) | Wire.read();
	return data;
}

// write to a given register
void TempratureSensor::write(uint8_t reg, uint8_t val)
{
	// start transmission to adress
	Wire.beginTransmission(I2C);
	// send register number
	Wire.write(reg);
	// send register  value
	Wire.write(val);
	// end transmission
	Wire.endTransmission();
}

// sets mode of conversion
void TempratureSensor::setMode(bool one_shot)
{
	uint8_t val = read(REG_CONFIG);
	// Once the device is in Shutdown mode, 
	// the CONFIG register needs to be written to again,  with bit 0 and bit 7 set <1> for one shot conversion
	// Temperature-TCN75AVOA.pdf © 2006 Microchip Technology Inc. DS21935C-page 21
	// for continous conversion, bit seven can be left as is because if bit 0 is set to <0> bit 7 will be ignored Table 5-6 page 21
	(!IBS(val,0) && one_shot)? SB(val,0) : CB(val,0);
	// set one-shot bit to <1> as well  -> Table 5-6 Page 21 .
	// thus we have 11 for bit 0 and bit 7 for one shot,  and 01 or 00 for continous conversion
	// and thus also avoiding bit 0 = 1 and bit 7 = 0; which is shutdown
	if(!IBS(val,7)) SB(val,7);  
	// write modified data to register
	this->write(REG_CONFIG,val);
	// and lets set our local variable
	this->oneShot = one_shot;
}

// public functions

// Initialises the sensor.
// partly from sample code shared on Sakai
void TempratureSensor::begin(){
	// 
	Wire.begin();
	// To access one shot mode, , the device needs to initially be in Shutdown mode. 
	// This is done by sending a byte to the CONFIG register with bit 0 set <1> and bit 7 cleared <0>
	// Temperature-TCN75AVOA.pdf © 2006 Microchip Technology Inc. DS21935C-page 21
	this->write(REG_CONFIG, 
				(3 << 3) /*Fault queue length: 6*/
				| _SB(2) /* Alert polarity: Active-high*/
				| _SB(1) /* Alert pin interrupt mode */
				| _SB(0) /* shutdown pin , shutdown mode activated by setting this pin to 1 and pin 7 to 0*/
				|( 0<<7 )/* One-shot pin should initially be set to 0 */
				);
	// default to one shot mode
	Serial.println();
	this->switchToOneShotMode();
	// inform about joystick commands one time
	Serial.println("**** To activate continous conversion mode, press and hold Joystick button ***");
	Serial.println();
}

// turns continous mode on.
void TempratureSensor::switchToContinuousMode(){
	if(this->oneShot) { // if one shot was true
		//set it to false, and reset onfig accordingly
		this->setMode(!this->oneShot);
		// print to console
		if(Serial){
			Serial.println("Switched to Continous mode");
		}
	}
}
// turns onshot mode on
void TempratureSensor::switchToOneShotMode(){
	
	if(!this->oneShot){ // if oneSHot was false
		//set it to false, and reset onfig accordingly
		this->setMode(!this->oneShot);
		// print to console too
		if(Serial){
			Serial.println("Switched to One shot mode");
		}
	}
}
// setting precision
void TempratureSensor::setResolution(uint8_t res){

	// retriev current value of configuration
	uint8_t regVal = read(REG_CONFIG);
	// clear bits 5 and 6;
	CB(regVal,5);
	CB(regVal,6);
	// set bits 5 and 6 to new resolution
	regVal |= ((res & 0x03) << 5); 
	// write modified value to register.
	write(REG_CONFIG, regVal);

}

// reads current temprature 
// and saves it to local temprature variable
void TempratureSensor::update(){

	// reseting and waiting for one-shot(bit 7) bit  isn't neccessary here
	// because we toggle shutdown(bit 0) bit in function that sets mode(@see setMode(bool oneShot) above)
	// according to manual if we let bit seven set to 1 after initialy setting it to 0, we can toggle between
	// Temperature-TCN75AVOA.pdf © 2006 Microchip Technology Inc. DS21935C-page 21
	// one-shot and continous just by toggling shutdown bit
	// but just incase 
	if(oneShot){ // if in one shot mode
		// set one shot bit to 1
		// shutdown pin is already taken care of by setMode() function
		this->write(REG_CONFIG, _SB(7));
		// wait for conversion to finish
		// and one-shot to be cleared by TCN after conversion is complete
		while(IBS(read(REG_CONFIG),7));
		
	}
	// read raw data from device
	uint16_t rawval = read(REG_AMBIENT);
	// Remove last 4 bits
	rawval = rawval >> 4;
	//  Temperature-TCN75AVOA.pdf equation 5-2  -> [ T_a = Code * 2^(-4)] © 2006 Microchip Technology Inc. DS21935C-page 13
	float temperature = (float)(rawval * 0.0625);
	this->temprature = temperature;
}

// reads actual temprature, either from local variable or read from device depending on @param immidiate
float TempratureSensor::getTemperature(bool immediate = false){
	// if we want the immidiate temprature
	// we have to update first
	if(immediate) update();
	// and return saved temprature
	return this->temprature;
}
