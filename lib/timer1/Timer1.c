/*
Implementation of Timer1 for a 16MHz AVR

Copyright (C) 2026  Jair Pereira Junior
SPDX-License-Identifier: GPL-3.0-or-later

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "Timer1.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <inttypes.h>

volatile uint32_t g_millis = 0;

ISR(TIMER1_COMPA_vect) {
	g_millis++;
}

void SetupTimer1(void) {
	/*
		references
		concept: making embedded systems elicia white page 111
		implementation, avr: https://www.pjrc.com/teensy/at90usb1286.pdf page 117
		
		#0 overview
		TCNT1 increases until a compare match occurs with OCR1A, then TCNT1 is cleared,
			at a match, OCF1A is set
			if OCIE1A is enabled and OCF1A set, it generates an interrupt (TIMER1_COMPA_vect)

		OCR1A: (16-bit) output compare register 1A
					- used as counter resolution, period time for waveforms
					- defines the TOP value for the counter
		OCF1A : (1-bit) output compare flag 1A
		OCIE1A: (1-bit) output compare interrupt

		#1 choosing a prescaler
			(assuming teensy++ 2.0 and clock_prescale_set(1))

			goal: we want precision of ms (1000 Hz)
			16 MHz = 16000 ticks per ms
				16 bit represents 65535, where 16000<65535 so prescaler of 1 is enough
				or 16MHz/(64*1000Hz)   = 250 ticks per ms; so a prescaler of 64 is also ok
				or 16MHz/(256*1000Hz)  = 62.5   ticks per ms; non-integer -> drift
				or 16MHz/(1024*1000Hz) = 15.625 ticks per ms; non-integer -> drift
			
			prescaler = 64 -> set CS11 and CS10 (CS: clock select)

		#2 choosing the top value
			prescaler = 64 -> 250 ticks per ms
			OCR1A = 249

		#3 WGM: waveform generation mode
			CTC Mode (Clear Timer on Compare)
			- TCNT1 increases until a compare match occurs with OCR1A, then TCNT1 is cleared
			
			CTC mode -> set WGM12
	*/	

    // initializing
	TCCR1A = 0; // ( 8-bit) timer counter control register 1A 
	TCCR1B = 0; // ( 8-bit) timer counter control register 1B (later, used to set CTC mode and prescaler)
	TCNT1  = 0; // (16-bit) timer counter value 1
	TIFR1  = (1 << OCF1A); // timer interrupt flag register 1; to clear it, set to 1; everything else is handled by the AVR

   	// a prescaler of 64: 250 ticks per ms 
	OCR1A = 249; // (16-bit) output compare register 1A

	// enable certain time interrupts (OCIE1->TIMER1_COMPA_vect)
	TIMSK1 = (1 << OCIE1A); // timer interrupt mask register 1

    // set CTC mode and prescaler
	TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10);
	
}

uint32_t get_current_ms(void) {
	uint32_t m;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		m = g_millis;
	}
	return m;
}
