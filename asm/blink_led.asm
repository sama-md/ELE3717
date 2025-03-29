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
.org 0x0000           ; A proxima instruncao em 0x0000
rjmp main             ; salte para main:

delay:
   clr     r17        ; defina r17 para 0
   clr     r18        ; defina r18 para 0
   ldi     r19, 10    ; defina r19 para 10
 
delay_loop:
   dec     r18        ; decremente r18 
   brne    delay_loop ; salte para delay_loop se r18 nao e 0
   dec     r17        ; decremente r17
   brne    delay_loop ; salte para delay_loop se r17 nao e 0
   dec     r19        ; decrament r19
   brne    delay_loop ; salte para delay_loop se r19 nao e 0
   ret                ; retorne

main:
   sbi     DDRB, 5    ; Defina PORTB pin 5 como saida

loop:
   cbi     PORTB, 5   ; Faca PB5=0
   rcall   delay      ; salte para delay 
   sbi     PORTB, 5   ; Faca PB5=1
   rcall   delay      ; salte para delay 
   rjmp    loop       ; salte para loop (infinitamente)