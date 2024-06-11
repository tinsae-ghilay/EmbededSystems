
#include "sleep_delay.h"
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>


// start watch dog interrupt
ISR(WDT_vect) {}

// sleep delay
// keeps chip in Power down mode for a duration of @param seconds
void sleep_delay(uint32_t seconds) {
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);

	while (seconds > 0) { // for the given seconds
		// @var  to interrupt 
		// because WDT is limited to maximum of 8 seconds
		// we will have to wake up device after some time
		// and repeat the proccess until enough time has passed
		uint8_t next_interrupt;
		if (seconds >= 8) { // maximum possible duration untill interrupt
			next_interrupt = WDTO_8S;
			seconds -= 8;
		} else if (seconds >= 4) { // if remaining time is less than 8 seconds,  we go accordingly
			next_interrupt = WDTO_4S;
			seconds -= 4;
		} else if (seconds >= 2) {
			next_interrupt = WDTO_2S;
			seconds -= 2;
		} else {
			next_interrupt = WDTO_1S;
			seconds -= 1;
		}
		// set the time until next interrupt
		wdt_enable(next_interrupt);

		// Enable Watchdog Interrupt
		// so it will interrupt sleep mode after the given time
		WDTCSR |= (1 << WDIE);
		// once interrupt watchdog is ready, 
		// enter sleep mode
		sleep_mode();
	}
	// disable watchdog once time is expired
	// and power down mode is done
	wdt_disable();
}




