

#include "ample.h"

// mark is a vriable to hold breaking points in time for switching colours
int32_t mark = 0;
bool Ample::readBtn()
{
    return bit_is_set(PINE,BUTTON_PIN);
}

// start setup
void Ample::start()
{
    lamp.begin();
    this->cState = RED;
    red();
    mark = millis();
    this->sensor.setup();


}

// loop gets called from loop function in main
// for continous run
void Ample::loop()
{
    if(this->isNight()){
        // after night mode it restarts from red
        if(this->cState != RED) this->cState = RED;
        // time should also be updated -> pseudo pause
        mark = millis(); 
        // blink yellow for night
        nightRun();
    }else{
        uint32_t now = millis();
        blockWalkers();
        allowEmergency();
        int32_t dur = now - mark;
        //uint8_t distance = sensor.getDistance();
        switch (this->cState){

        // on RED
        case RED:
            this->red();
            // if red on for 7 seconds-> switch to yellow
            if(dur > 7000){
                this->cState = YELLOW;
                mark = now;
            }
            break;

        // on YELLOW
        case YELLOW:
            this->yellow();
            // if yellow on for 3 seconds, switch to red or green
            if(dur > 3000){
            if(this->toRed){
                this->cState = RED;
            }else{
                this->cState = GREEN;
            }
            mark = now; 
            }
            break;

        // on GREEN
        case GREEN:
            this->green();
            // if green lit for 5 seconds, blink
            if(dur > 5000){
                this->cState = BLINK;
                mark = now; 
            }
            break;
        
        // Blinking
        default:
            this->blink();
            if(dur > 2000){
                this->cState = YELLOW;
                mark = now;
                // TODO BUG here
            }
            break;
        }
    }
}
// we control pressed and released button
// by comparing immidiate button state and recorded state
// if eg. button is HIGH and recorded state is PRESSED, button press is not new and should be ignorred
// if button is LOW and recorded state is PRESSED, we report it as released.
// if button is HIGH and recorded state is RELEASED, we report it as PRESSED because button is high after being released.
uint32_t p_strt = 0;
bool Ample::btnPressed()
{
    // we get button status
    bool pressed = readBtn(); 
    // if button is HIGH and previous state is RELEASED
    if(pressed && this->bState == RELEASED){
        // means button is newly pressed
        this->bState = PRESSED;
        // we record the start of button press for future proccessing
        p_strt = millis();
        // and return true.
        return true;
    }else if(millis() - p_strt > 250 && !pressed){ /*if button has not been pressed for 250 micro seconds, consider it released*/

        this->bState = RELEASED;
    }
    return false;
}

// returns true if light intensity is below 200
bool Ample::isNight()
{
    uint8_t intensity = analogRead(A2);
    //Serial.print("Lignt intensity : ");
    //Serial.println(intensity);
    return intensity < 200;
}

// turn red LED  on
void Ample::red()
{
    on(30,0,0);
    this->toRed = false;
}

// gree LED on
void Ample::green()
{
    on(0,30,0);
    this->toRed = true;
    
}

// red and green LEDs on to produce yellow
void Ample::yellow()
{
    on(30,30,0);
}

// turns LED on based on passed colors
void Ample::on(uint8_t red, uint8_t green, uint8_t blue)
{
    lamp.clear();
    lamp.setPixelColor(0, lamp.Color(red/*red*/, green/*green*/, blue/*blue*/));
    lamp.show();
    this->lState = ON;
}

// clears colors and turns LEDs off
void Ample::off()
{
    lamp.clear();
    lamp.show();
    this->lState = OFF;
}

// blinking of lights
uint32_t tmp_mark = 0;
void Ample::blink()
{
    
    // start of on or off state
    uint32_t tmp = millis();
    if(tmp - tmp_mark > 500){ /* 0.5 seconds passed */
        if(this->lState == OFF){ // light was off
            
            this->on(0,60,0);
        }else{ // light was on
            // switch off
            off();
        }
        tmp_mark = tmp;
    } 
}

void Ample::allowEmergency()
{
    if(this->btnPressed()){
        Serial.println("Emergency button detected and is being handled");
        this->toRed = false;
        switch (this->cState)
        {
        case RED:
            this->cState = YELLOW;
            mark = millis();
            break;
        case GREEN:
            mark+=5000;
            break;
        default:
            if(this->toRed) this->toRed = false;
            break;
        }
    }  
}
void Ample::nightRun()
{
    
    if(this->lState == ON){ //light was on
        off();
    }else{   // light was off
        on(30,30,0);
    }
    Serial.println("On a night run");
    // delay
    delay(500);
    

}
// to avoid repeated increment of time on every motion detected
// we save arival time of walkers
// if motion is detected again within 5 seconds, we ignore it, considering it to be the same ocurance
// if stayed more than 5 seconds, another 5 seconds will be added to duration of red
uint32_t arival = 0;
void Ample::blockWalkers(){
    uint16_t now = millis();
    int16_t duration = now - arival;
    // if less than 5 seconds have passed since first motion detection,
    // ignore triger and do nothing.
    if(duration < 5000){
    // distance of nearest object
        uint8_t distance = this->sensor.getDistance();
        // motion detected // obstacle detected
        if(distance < 5 && !(this->jWalking)){
            Serial.print("Motion detected and is being handled :");
            // record first detection 
            arival = millis();
            if(this->cState == RED){ /* light is red */
                Serial.println(" Duration of red extended");
                // prolog red by 5 seconds
                mark+=5000;
            }else if(this->cState == GREEN){ /* light is green */
                // blink and go to red.
                mark = millis();
                this->cState = BLINK;
                Serial.println(" going to red");
            }
            // if light was blinking ar was yellow, keep going
            // but check if yellow transition
            // if it was going to be green, change it so it goes to red
            if(!this->toRed) this->toRed = true;
            // mark the motion has been detected and avoid repeat
            this->jWalking = true;
        }
        // if no motion is detected for 5 seconds
        // clear motion detection key
        if(distance > 19 && (this->jWalking)){
            this->jWalking = false;
        }
    }

}
