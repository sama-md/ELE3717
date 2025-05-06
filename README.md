# ELE3717 - Sistemas Microcontrolados

[![Main](https://img.shields.io/badge/main%20language-PT-blue)](/../../)

Este repositório contém o material de suporte utilizado na componente curricular Sistemas Microcontrolados do curso de Engenharia Mecatrônica da Universidade Federal do Rio Grande do Norte (UFRN).

### Conteúdo

**AVR** introdução ao ATMega328P em assembly

- Código fonte para piscar um led na porta PB5 ([blink_led.asm](https://github.com/sama-md/ELE3717/blob/main/asm/blink_led.asm))
- Código fonte para acionar o led na porta PB5 de acordo com a entrada na porta PC0 ([blink_led.asm](https://github.com/sama-md/ELE3717/blob/main/asm/io_read_pin.asm))
- Código fonte para ajustar pwm por entrada analógica ([ad_timer2_pwm.asm](https://github.com/sama-md/ELE3717/blob/main/asm/ad_timer2_pwm.asm))

**AVR** introdução ao ATMega328P em Ansi C

- Código fonte para piscar um led na porta PB5 com frequência definida pelo conversor A/D utilizando interrupção no A/D ([ad_iadc_io.c](https://github.com/sama-md/ELE3717/blob/main/c/ad_iadc_io.c))
- Código fonte para piscar um led na porta PB5 com frequência definida pelo conversor A/D ([ad_io.c](https://github.com/sama-md/ELE3717/blob/main/c/ad_io.c))
- Código fonte para alternar o estado do led na porta PB5 utilizando a interrupção do comparador analógico ([adc_ianc_io.c](https://github.com/sama-md/ELE3717/blob/main/c/adc_ianc_io.c))
- Código fonte para escrever e em seguida ler um dado da EEPROM([eeprom_rw.c](https://github.com/sama-md/ELE3717/blob/main/c/eeprom_rw.c))
- Código fonte para alternar o estado do led na porta PB5 utilizando interrupção na mudança ([io_rpin_ich.c](https://github.com/sama-md/ELE3717/blob/main/c/io_rpin_ich.c))
- Código fonte para alternar o estado do led na porta PB5 utilizando interrupção externa ([io_rpin_iext.c](https://github.com/sama-md/ELE3717/blob/main/c/io_rpin_iext.c))
- Código fonte para piscar um led na porta PB5 ([io_wpin.c](https://github.com/sama-md/ELE3717/blob/main/c/io_wpin.c))
- Código fonte para piscar um led na porta PB5 utilizando MDE ([io_wpin_mde.c](https://github.com/sama-md/ELE3717/blob/main/c/io_wpin_mde.c))
- Código fonte para piscar um led na porta PB5 utilizando MDE com ponteiro ([io_wpin_mde_pointer.c](https://github.com/sama-md/ELE3717/blob/main/c/io_wpin_mde_pointer.c))
- Código fonte para enviar dado via porta spi ([spi_master_io.c](https://github.com/sama-md/ELE3717/blob/main/c/spi_master_io.c))
- Código fonte para receber dado via porta spi ([spi_slave_io.c](https://github.com/sama-md/ELE3717/blob/main/c/spi_slave_io.c))
- Código fonte para piscar um led na porta PB5 utilizando o timer 0 ([timer0_io.c](https://github.com/sama-md/ELE3717/blob/main/c/timer0_io.c))
- Código fonte para piscar um led na porta PB5 utilizando interrupção no timer 0 ([timer0_iovf_io.c](https://github.com/sama-md/ELE3717/blob/main/c/timer0_iovf_io.c))
- Código fonte para piscar um led na porta PB5 utilizando interrupção no timer 1 ([timer1_icmpa_io.c](https://github.com/sama-md/ELE3717/blob/main/c/timer1_icmpa_io.c))
- Código fonte para aplicar sinal pwm na porta PB3 ([timer2_pwm.c](https://github.com/sama-md/ELE3717/blob/main/c/timer2_pwm.c))
- Código fonte para enviar dado via porta twi ([twi_master_io.c](https://github.com/sama-md/ELE3717/blob/main/c/twi_master_io.c))
- Código fonte para receber dado via porta twi ([twi_slave_io.c](https://github.com/sama-md/ELE3717/blob/main/c/twi_slave_io.c))
- Código fonte para fazer um eco na porta serial ([uart_echo.c](https://github.com/sama-md/ELE3717/blob/main/c/uart_echo.c))

---
### Licença

Shield : [![License: CC BY-NC-ND 4.0](https://img.shields.io/badge/License-CC%20BY--NC--ND%204.0-lightgrey)](https://creativecommons.org/licenses/by-nc-nd/4.0/)

Esta obra tem a [licença Creative Commons Atribuição-NãoComercial-SemDerivações 4.0 Internacional](https://creativecommons.org/licenses/by-nc-nd/4.0/deed.pt_BR).

[![CC BY-NC-ND 4.0](https://licensebuttons.net/l/by-nc-nd/4.0/88x31.png)](https://creativecommons.org/licenses/by-nc-nd/4.0/deed.pt_BR)

 
