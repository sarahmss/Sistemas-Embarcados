/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lab04_3.ino                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:21:55 by smodesto          #+#    #+#             */
/*   Updated: 2025/05/01 20:21:55 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <avr/interrupt.h>

#define OUTPUT_PIN      (1 << PB2) // Pin  10 (PB2 == OC1B)

// F_pwm = F_clk/(N * (TOP + 1)) ; F_clk = 16 MHz   
  

// TOP == 500000 -> F_pwm == 2 Hz
#define TOP_2Hz         500000     
#define DUTY_CYCLE_50   250000        


void setup(void)
{

    cli();
    // 
    DDRB |= OUTPUT_PIN;
    PORTB &= ~OUTPUT_PIN;

    // TCNTn: Timer/Counter register ()
    TCNT1 = 0;
    OCR1A = 0;
    OCR1B = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;

    // OCRnX: Outupt Compare Register ->  stores the compare value
    OCR1A = TOP_2Hz;
    OCR1B = DUTY_CYCLE_50;


    // TCCRnX: Timer/Counter Control Register 


    // WGMn: Waveform Generation Mode bit
    // WGM03:0 = 0b0100 (CTC with OCR1A as TOP)
    TCCR1B &= ~ (1 << WGM13); 
    TCCR1B |= (1 << WGM12);
    TCCR1A &= ~ (1 << WGM11); 
    TCCR1A &= ~ (1 << WGM10); 


    // Set interrupt on compare match
    TIMSK1 |= (1 << OCIE1B);


    // CSn: Clock select
    // CS12:0 = 0b010 (Prescaler == 8 -> F_clck / 8) 
    TCCR1B &= ~(1 << CS12);
    TCCR1B |= (1 << CS11); 
    TCCR1B &= ~(1 << CS10) ;

    sei();
}

ISR (TIMER1_COMPB_vect)
{
    PORTB ^= OUTPUT_PIN;                // Toggle LED state
}


void loop(void){

}