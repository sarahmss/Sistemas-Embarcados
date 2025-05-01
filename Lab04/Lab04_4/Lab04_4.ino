/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lab04_4.ino                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:33:58 by smodesto          #+#    #+#             */
/*   Updated: 2025/05/01 20:33:58 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <avr/io.h>
#include <avr/interrupt.h>

#define OUTPUT_PIN      (1 << PB2) // Pin  10 (PB2 == OC1B)
#define INPUT_PIN       (1 << PD2)  // pin 2 (PD2 == INT0)

// F_pwm = F_clk/(N * (TOP + 1)) ; F_clk = 16 MHz   
  

// TOP == 500000 -> F_pwm == 2 Hz
#define TOP_2Hz         500000     
#define DUTY_CYCLE_50   250000        

#define TIME_45  63 // ms
#define TIME_120 167 // ms

volatile uint cycles = 0;  // 


void setup(void)
{
    Serial.begin(9600);
    cli();
// ================================== Detector de Zero ================================
    // set INPUT_PIN as input
    DDRD &= ~INPUT_PIN;

    // Enable External Interrupts in INT0  == Pin 2
    EIMSK |= (1 << INT0);

    // Bits to set mode in INT0 01 = CHANGE
    EICRA &= ~(1 << ISC00);  // Clear ISC00
    EICRA |=  (1 << ISC01);  // Set ISC01


// ================================== Temporizador ====================================
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
    Serial.print("Quantidade de ciclos: ");
    Serial.println(cycles);}


/*
  @brief: defines the routine for INT0 interrupt (INPUT_PIN)
*/
ISR(INT0_vect) {

    static uint TimeInit = millis();
    uint CurrentTime = millis();

    if (CurrentTime - TimeInit <= TIME_45){
        cycles += 1;
    }
}

void loop(void){

}