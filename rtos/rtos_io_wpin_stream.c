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
#include "freertos/stream_buffer.h"

static void vTask_wpin_send(void *pvParameters);
static void vTask_wpin_recv(void *pvParameters);

#define STREAM_SZ 10
#define DATA_SZ   9

StreamBufferHandle_t xStream;

int main( void ){

	DDRB = 0x28;

	xStream = xStreamBufferCreate(STREAM_SZ, 1);
	xTaskCreate( vTask_wpin_send, "give", 256, NULL, 1, NULL );
	xTaskCreate( vTask_wpin_recv, "take", 256, NULL, 2, NULL );
	vTaskStartScheduler();
	for( ;; );
}

static void vTask_wpin_send( void *pvParameters ){
	
	uint8_t ucDataBuffer[]={0x00,0x02,0x04,0x08,0x00,0x08,0x04,0x02,0x00};
	size_t  xBytesSent;
	
	for( ;; ){
		PORTB ^= (1<<PORTB5);
		xBytesSent = xStreamBufferSend(xStream, ucDataBuffer, DATA_SZ, portMAX_DELAY);
		vTaskDelay( 1000 );
	}
}

static void vTask_wpin_recv( void *pvParameters ){

	uint8_t ucRecBuffer[DATA_SZ];
	size_t xRecBytes;
	
	for( ;; ){
		xRecBytes = xStreamBufferReceive(xStream, ucRecBuffer, DATA_SZ, portMAX_DELAY);
		for(uint8_t i=0;i<9;i++){
			PORTB =  ucRecBuffer[i];
			vTaskDelay( 50 );
		}
	}
}
