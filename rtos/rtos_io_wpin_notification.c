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

static void vTask_wpin_give(void *pvParameters);
static void vTask_wpin_take(void *pvParameters);

TaskHandle_t vTask_give_handle = NULL;
TaskHandle_t vTask_take_handle = NULL;

int main( void ){

	DDRB = 0x28;

	xTaskCreate( vTask_wpin_give, "give", 256, NULL, 1, &vTask_give_handle );
	xTaskCreate( vTask_wpin_take, "take", 256, NULL, 1, &vTask_take_handle );
	vTaskStartScheduler();
	for( ;; );
}

static void vTask_wpin_give( void *pvParameters ){
	
	uint16_t count=0;
	
	for( ;; ){
		PORTB ^= (1<<PORTB5);
		count++;
		if(count == 3){
			xTaskNotifyGive(vTask_take_handle);
			count = 0;
		}
		vTaskDelay( 50 );
	}
}

static void vTask_wpin_take( void *pvParameters ){

	uint32_t notificationValue;
	
	for( ;; ){
		notificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		if( notificationValue > 0 ) {
			PORTB ^= (1<<PORTB3);
		}
	}
}


