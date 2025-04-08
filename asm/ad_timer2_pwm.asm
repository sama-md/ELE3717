;
; Copyright (C) 2025 Samaherni M. D.
; Universidade Federal do Rio Grande do Norte (UFRN)
; 
; This file is part of ELE3717 project (https://github.com/sama-md/ELE3717/). 
; It is subject to the license terms in the LICENSE file found in the top-level 
; directory of this distribution. 
;
; Licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 
; 4.0 International License;
; you may not use this file except in compliance with the License.
; You may obtain a copy of the License at
;
;  (EN)  https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
;  (PT)  https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.pt
;
; Unless otherwise separately undertaken by the Licensor, to the extent possible, 
; the Licensor offers the Licensed Material "as-is" and "as-available", and makes
; no representations or warranties of any kind concerning the Licensed Material, 
; whether express, implied, statutory, or other.
; See the License for the specific language governing permissions and
; limitations under the License.
;

.include "m328pdef.inc"
.org 0x0000              ; A proxima instruncao em 0x0000
rjmp main                ; salte para main:   

main:    
	cbi     DDRC, 0      ; defina PC pin 0 como entrada
	sbi     DDRB, 3      ; defina PB pin 3 como saida

	ldi     r16, 0x60
	sts     ADMUX, r16   ; defina AVcc como referencia e ajuste a esquerda             
	ldi     r16, 0x00
	sts     ADCSRB, r16  ; defina o modo de trigger free running		
	ldi     r16, 0x87    
	sts     ADCSRA, r16  ; habilite o adc e utilize uma pre-escala de 128

	ldi     r16,0x83
	sts     TCCR2A,r16   ; defina o modo de opercao fast pwm
	ldi     r16,0x01
	sts     TCCR2B,r16   ; defina o clock do timer 2 sem pre-escala 
	sts     TCNT2,r16    ; inicialize o timer 2 em 0x01
	ldi     r16,0x3F     
	sts     OCR2A,r16    ; inicialize o duty cycle do pwm em 0x3F

loop:
	rcall   Radc         ; salte para Radc (funcao para ler adc)
	sts     OCR2A,r22    ; atualize o valor do duty cycle do pwm
	rjmp    loop      

Radc:   
	ldi     r20, 0xC7    
	sts     ADCSRA,r20   ; inicie a conversao 

loop_adc:
	lds     r20, ADCSRA  ; carregue no registrador 20 o valor de ADCSRA
	sbrs    r20, ADIF    ; verifique se o processo de conversao finalizou
	rjmp    loop_adc 
	lds     r21, ADCL    ; carregue o valor (L) do conversor ad no registrador 21
	lds     r22, ADCH    ; carregue o valor (H) do conversor ad no registrador 22
	ret                  ; retorne  