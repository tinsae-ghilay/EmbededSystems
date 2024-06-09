
#include "sleep_delay.h"
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>


ISR(WDT_vect) {}


void sleep_delay(uint32_t seconds) {
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);

	while (seconds > 0) {

		uint8_t wdt_time_param;
		if (seconds >= 8) {
			wdt_time_param = WDTO_8S;
			seconds -= 8;
		} else if (seconds >= 4) {
			wdt_time_param = WDTO_4S;
			seconds -= 4;
		} else if (seconds >= 2) {
			wdt_time_param = WDTO_2S;
			seconds -= 2;
		} else {
			wdt_time_param = WDTO_1S;
			seconds -= 1;
		}

		wdt_enable(wdt_time_param);

		// Enable Watchdog Interrupt
		// We need to reenable the watchdog interrupt every time the interrupt-handler gets executed
		WDTCSR |= (1 << WDIE);

		sleep_mode();
	}

	wdt_disable();
}




