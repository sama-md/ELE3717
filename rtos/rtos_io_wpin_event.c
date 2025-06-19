/*
 * rtos_io_wpin_event.c
 *
 * Created: 19/06/2025 16:23:45
 * Author : UFRN
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#define	BIT2	( (EventBits_t)( 0x01 <<2) )
#define BIT1	( (EventBits_t)( 0x01 <<1) )

static void vTask_mde(void *pvParameters);
static void vTask_wpin(void *pvParameters);

volatile uint8_t fsm_state = 0;
EventGroupHandle_t myEventGroup;  

int main( void ){

	DDRB = 0x2E;

	myEventGroup = xEventGroupCreate();
	xTaskCreate( vTask_mde,   "mde", 256, NULL, 1, NULL );
	xTaskCreate( vTask_wpin, "wpin", 256, NULL, 2, NULL );
	vTaskStartScheduler();
	for( ;; );
}

static void vTask_mde( void *pvParameters ){

	for( ;; ){
		PORTB ^= (1<<PORTB5);
		switch (fsm_state){
			case 0:
				xEventGroupSetBits(myEventGroup, BIT2 | BIT1);
				fsm_state = 1;
			break;
			case 1:
				xEventGroupSetBits(myEventGroup, BIT1);
				fsm_state = 2;
			break;
			case 2:
				xEventGroupSetBits(myEventGroup, BIT2);
				fsm_state = 0;
			break;
			default:
				fsm_state = 0;
			break;
		}
		vTaskDelay(50);
	}
}

static void vTask_wpin( void *pvParameters ){

	EventBits_t evb_result;
	
	for( ;; ){
		evb_result = xEventGroupWaitBits(myEventGroup, (BIT2 | BIT1), pdTRUE, pdFALSE, portMAX_DELAY );
		if( ( evb_result & ( BIT2 | BIT1 ) ) == ( BIT2 | BIT1 ) ){
			PORTB = 0x08;
		}
		else if( ( evb_result & BIT2 ) != 0 ){
			PORTB = 0x04;
		}
		else if( ( evb_result & BIT1 ) != 0 ){
			PORTB = 0x02;
		}
		else{
			PORTB = 0x00;
		}
	}
}

