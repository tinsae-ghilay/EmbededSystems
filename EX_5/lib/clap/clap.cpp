
/*
* created by TGK
* on jun 22/2024
* for Embeded systems
*/


#include "clap.h"

void ClapDetection::setup(uint8_t mic, uint16_t threshold)
{
    // microphone pin
    this->mic = mic;
    // minimum sound threshold that we can consider clap
    this->threshold = threshold;
}

// recording breaking time
uint32_t brk = millis();

// updates clap state
// should be called on a loop
void ClapDetection::update()
{
    bool clap = false;
    // below code adapted from sample on gitHub from Olimex SOFTWARE
    // taking a sequence of samples to determine whether there is noise or not
    uint16_t max = 0, min = 1024, amp = 0;
    for(int i = 0; i < 70; i++)
    {
        uint16_t sound = analogRead(mic);
        // if there is a new high update max
        if (sound > max) max = sound;
        // if there is new low update min
        if (sound < min) min = sound;
        // then we get our amplitude
        amp = max - min;
    }
    // time stamp to identify claps that happen intentionaly
    // identified by the duration between claps
    uint32_t now = millis();
    uint16_t dur = now - brk;

    // sound should be louder than a predetermined threshold
    if(amp > threshold){
        // if sound louder than threshold happens within 100 - 700 milliseconds
        // its considered as a clap
        // if not, we just record the time for the next
        if(dur > 100){
            clap = true;
        }
        brk = now;
    }
    
    // if more than 700 milliseconds have elapsed since last clap
    // it is time to take action, depending on number of claps recorded
    if(dur > 700){

        if(cl_count > 0){
            Serial.print(cl_count);
            Serial.println(" Claps detected");
            // two claps
            if(cl_count == 2) this->claps = DOUBLE;//Serial.println("TWO CLAPS, MUST DO SOME THING ON LED");
            // three claps
            if(cl_count == 3) this->claps = TRIPPLE;//Serial.println("THREE CLAPS, MUST DO SOME THING ON LED");
            // reset clap count
            cl_count = 0;
        }else{ // clap counting reset, so set state to NONE
            this->claps = NONE;
        }
    }
    // if another clap happens within acceptable time frame
    // we update clap count
    if(clap){
        cl_count++;
    }
}

// returns clap state, NONE-> no claps, DOUBLE and TRIPPLE
clap ClapDetection::getState()
{
    return this->claps;
}
