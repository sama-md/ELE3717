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
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

static void vTask_mde(void *pvParameters);
static void vTask_wpin(void *pvParameters);

QueueHandle_t xQueue;
volatile uint8_t fsm_state = 0;

int main( void ){

	DDRB = 0x0E;

	xQueue = xQueueCreate(5, sizeof( int32_t ));
	xTaskCreate( vTask_mde,  "mde",  256, NULL, 1, NULL );
	xTaskCreate( vTask_wpin, "wpin", 256, NULL, 2, NULL );
	vTaskStartScheduler();
	for( ;; );
}

static void vTask_mde( void *pvParameters ){

	int32_t lValueToSend = 0;
	BaseType_t xStatus;

	for( ;; ){
		switch (fsm_state){
			case 0:
				lValueToSend = 0x02;
				fsm_state = 1;
				break;
			case 1:
				lValueToSend = 0x04;
				fsm_state = 2;
				break;
			case 2:
				lValueToSend = 0x08;
				fsm_state = 3;
				break;
			case 3:
				lValueToSend = 0x00;
				fsm_state = 0;
				break;
			default:
				break;
		}
		xStatus = xQueueSendToBack( xQueue, &lValueToSend, 0 );
		vTaskDelay(50);
	}
}

static void vTask_wpin( void *pvParameters ){

	int32_t lReceivedValue;
	BaseType_t xStatus;
	const TickType_t xTicksToWait = pdMS_TO_TICKS( 100 ); 

	for( ;; ){
		xStatus = xQueueReceive( xQueue, &lReceivedValue, xTicksToWait );
		PORTB = lReceivedValue;
	}
}
