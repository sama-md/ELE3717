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
#include <util/delay.h>  

int main(void)           
{
	DDRB = 0b00100000;    
	
	while(1)              
	{
		PORTB^=(1<<PB5);   
		_delay_ms(500);    
	}
	return 0;
}

