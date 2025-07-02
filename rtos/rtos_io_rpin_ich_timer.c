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

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

static void vTask_wpin_dumb(void *pvParameters);
static void vTaskTimer (TimerHandle_t xTimer);

TimerHandle_t	my_timer;

int main( void ){

	DDRB = 0x2E;
	DDRC = 0x00;

	PCICR = 0x06;
	PCMSK1 = 0x06;

	my_timer = xTimerCreate("my_timer", 200, pdTRUE, NULL, vTaskTimer);
	xTimerStart(my_timer, 0);
	xTaskCreate( vTask_wpin_dumb, "dumb", 256, NULL, 1, NULL );
	sei();
	vTaskStartScheduler();
	for( ;; );
}

static void vTask_wpin_dumb( void *pvParameters ){
	
	uint16_t count=0;
	
	for( ;; ){
		PORTB ^= (1<<PORTB2);
		count++;
		if(count == 3){
			count = 0;
		}
		vTaskDelay( 50 );
	}
}

void vTaskTimer(TimerHandle_t xTimer)
{
	PORTB ^= (1<<PORTB5);
}

ISR(PCINT1_vect) {

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	PORTB ^= (1<<PORTB3);
	
	if ((PINC & 0x02) == 0){
		xTimerChangePeriodFromISR( my_timer, 200, &xHigherPriorityTaskWoken );
	}
	if ((PINC & 0x04) == 0){
		xTimerChangePeriodFromISR( my_timer,  50, &xHigherPriorityTaskWoken );	
	}
	portYIELD_FROM_ISR();
}

