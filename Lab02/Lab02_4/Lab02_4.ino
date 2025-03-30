/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lab02_4.ino                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:07:01 by smodesto          #+#    #+#             */
/*   Updated: 2025/03/30 19:07:01 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define OUTPUT_PIN    (1 << PB4)  // pin 12 (PB4)
#define INPUT_PIN_3   (1 << PD3)  // pin 3 (PD3)
#define INPUT_PIN_2   (1 << PD2)  // pin 2 (PD2)

void setup(void) {

  // Disable External Interrupts globally
  cli();

  // set OUTPUT_PIN as output
  DDRB |= OUTPUT_PIN;

  // set INPUT_PIN_3 as input
  DDRD &= ~INPUT_PIN_3;
  
  // set INPUT_PIN_2 as input
  DDRD &= ~INPUT_PIN_2;

  // set internal Pull-up
  PORTD |= INPUT_PIN_3;
  PORTD |= INPUT_PIN_2;

  // Enable External Interrupts in INT1  == Pin 3
  EIMSK |= (1 << INT1);
  
  // Bits to set mode in INT1 10 = Falling
  EICRA |=  (1 << ISC11);  // Set ISC11
  EICRA &= ~(1 << ISC10);  // Clear ISC10

  // Enable External Interrupts in INT0  == Pin 2
  EIMSK |= (1 << INT0);

  // Bits to set mode in INT0 10 = Falling
  EICRA |=  (1 << ISC00);  // Set ISC00
  EICRA &= ~(1 << ISC01);  // Clear ISC01
  
  // Enable External Interrupts globally
  sei();
}

/*
  @brief: defines the routine for INT1 interrupt
*/
ISR(INT1_vect) {
 PORTB ^= OUTPUT_PIN;
}

/*
  @brief: defines the routine for INT1 interrupt
*/
ISR(INT0_vect) {
 PORTB ^= OUTPUT_PIN;
}

void loop(void) {
  
}