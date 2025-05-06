//
// Copyright (C) 2025 Samaherni M. D.
// Universidade Federal do Rio Grande do Norte (UFRN)
// 
// This file is part of ELE3717 project (https://github.com/sama-md/ELE3717/). 
// It is subject to the license terms in the LICENSE file found in the top-level 
// directory of this distribution. 
//
// Licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 
// 4.0 International License;
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//  (EN)  https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
//  (PT)  https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.pt
//
// Unless otherwise separately undertaken by the Licensor, to the extent possible, 
// the Licensor offers the Licensed Material "as-is" and "as-available", and makes
// no representations or warranties of any kind concerning the Licensed Material, 
// whether express, implied, statutory, or other.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <avr/io.h>
#include <avr/interrupt.h>

const unsigned long CYCLES=1500;

void my_delay(unsigned long myADC);

int main(void) {
	DDRB |= (1<<PB5);                   
	PORTB &= ~(1<<PB5);                 
	DDRC  &=~(1<<PB0);
	ADMUX=(1<<REFS0);                   
	ADCSRA=0x07;                        
	ADCSRB=0x00;                        
	ADCSRA |=(1<<ADEN)|(1 << ADIE);                   
	sei();                              
	ADCSRA |= (1 << ADSC);              
	for(;;);
	return 0;
}

ISR(ADC_vect)
{
	PORTB^=(1<<PB5);                 
	my_delay(ADC);                  
	ADCSRA |= (1 << ADSC);              
}

void my_delay(unsigned long myADC){

	for (unsigned int j = 0; j <= (myADC+15); j++){
		for (unsigned long i = 0; i < CYCLES; i++);
	}
	
	return;
}