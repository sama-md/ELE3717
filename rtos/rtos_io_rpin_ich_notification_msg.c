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

static void vTask_wpin_dumb(void *pvParameters);
static void vTask_wpin_take(void *pvParameters);

TaskHandle_t vTaskDumb_h = NULL;
TaskHandle_t vTaskTake_h = NULL;

volatile uint8_t fsm_state = 0;

int main( void ){

	DDRB = 0x2E;
	DDRC = 0x00;

	PCICR = 0x02;
	PCMSK1 = 0x02;

	xTaskCreate( vTask_wpin_dumb, "dumb", 256, NULL, 1, &vTaskDumb_h );
	xTaskCreate( vTask_wpin_take, "take", 256, NULL, 2, &vTaskTake_h );
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

static void vTask_wpin_take( void *pvParameters ){

	int32_t lReceivedValue;

	lReceivedValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	for( ;; ){
		lReceivedValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		PORTB = lReceivedValue & 0x0A;
	}
}

ISR(PCINT1_vect) {

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	uint32_t lValueToSend = 0;

	switch (fsm_state){
		case 0:
		lValueToSend = 0x02;
		fsm_state = 1;
		break;
		case 1:
		lValueToSend = 0x08;
		fsm_state = 2;
		break;
		case 2:
		lValueToSend = 0x00;
		fsm_state = 0;
		break;
		default:
		break;
	}
	PORTB ^= (1<<PORTB5);
	xTaskNotifyFromISR( vTaskTake_h, lValueToSend, eSetValueWithOverwrite, &xHigherPriorityTaskWoken );
	portYIELD_FROM_ISR();
}

