/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LAb04_1.ino                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:22:03 by smodesto          #+#    #+#             */
/*   Updated: 2025/05/01 19:22:03 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    PWM cc de 20 kHz / 32 kHz
        1. Definir pino x como saida
        2. Armazenar no Registrador A o valor de TOP
        3. Armazenar no Registrador B o valor do Duty Cycle
        4. Definir modo Fast PWM (TOP variável)
        5. Configurar modo de comparação (não invertido)
        6. Definir Prescaler
*/
 
#include <avr/io.h>
#include <avr/interrupt.h>

#define OUTPUT_PIN      (1 << PD5) // Pin 5 (PD5 == OC0B)

// F_pwm = F_clk/(N * (TOP + 1)) ; F_clk = 16 MHz     

// TOP == 100 -> F_pwm == 20 kHz
#define TOP_20kHz       100     
#define DUTY_CYCLE_50   50         
#define DUTY_CYCLE_75   75         

// TOP == 62 -> F_pwm == 31.746 kHz
#define TOP_32kHz       62     
#define DUTY_CYCLE_25   15         


void setup(void)
{

    // 
    DDRD |= OUTPUT_PIN;
    PORTD &= ~OUTPUT_PIN;

    // TCNTn: Timer/Counter register ()
    TCNT0 = 0;
    OCR0A = 0;
    OCR0B = 0;
    TCCR0A = 0;
    TCCR0B = 0;

    // OCRnX: Outupt Compare Register ->  stores the compare value
    OCR0A = TOP_20kHz;
    OCR0B = DUTY_CYCLE_25;


    // TCCRnX: Timer/Counter Control Register 

    // COMBnX: Compare Match Output B Mode 
    // COM0B1:0 = 0b10 (non-inverting mode - HIGH at bottom, LOW on Match)
    // OC0B -> store
    TCCR0A |= (1 << COM0B1);   
    TCCR0A &= ~(1 << COM0B0);    

    // WGMn: Waveform Generation Mode bit
    // WGM02:0 = 0b111 (Fast PWM with OCR0A as TOP)
    TCCR0B |= (1 << WGM02);
    TCCR0A &= ~ (1 << WGM01); 
    TCCR0A |= (1 << WGM00);

    // CSn: Clock select
    // CS02:0 = 0b010 (Prescaler == 8 -> F_clck / 8) 
    TCCR0B &= ~(1 << CS00);
    TCCR0B |= (1 << CS01); 
    TCCR0B &= ~(1 << CS02) ;

}


void loop(void){

}
