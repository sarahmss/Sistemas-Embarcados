/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LAb04_1.ino                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:27:23 by smodesto          #+#    #+#             */
/*   Updated: 2025/04/23 22:27:23 by smodesto         ###   ########.fr       */
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

#define OUTPUT_PIN      (1 << DDD6) // Pin 6 (PD6 == OC0A): Output Compare

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

    // OCRnX: Outupt Compare Register ->  stores the compare value
    OCR0A = TOP_20kHz;
    OCR0B = DUTY_CYCLE_50;

    // TCNTn: Timer/Counter register ()
    TCNT0 = 0;

    // TCCRnX: Timer/Counter Control Register 

    // COMAnX: Compare Output Mode bit
    // COM0A1:0 = 0b10 (non-inverting mode - HIGH at bottom, LOW on Match)
    TCCR0A |= (1 << COM0A1);    
    TCCR0A &= ~(1 << COM0A0);   

    // WGMn: Waveform Generation Mode bit
    // WGM02:0 = 0b111 (Fast PWM with OCR0A as TOP)
    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    TCCR0B |= (1 << WGM02);

    // CSn: Clock select
    // CS02:0 = 0b010 (Prescaler == 8 -> F_clck / 8) 
    TCCR0B |= (1 << CS01); 
    TCCR0B &= ~((1 << CS02) | (1 << CS00));

}


void loop(void){

}

