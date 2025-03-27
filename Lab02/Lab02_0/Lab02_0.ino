/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lab02_0.ino                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:04:03 by smodesto          #+#    #+#             */
/*   Updated: 2025/03/26 20:04:03 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
EIMSK - Enables INT0 and INT1 
EICRA - Defines how INT0 and INT1 are enabled (LOW, RISING, FALLING ou CHANGE)
  - 0 0 = enables interrupt in LOW level
  - 1 0 = enables interrupt in a change of states
  - 1 0 = enables intterupt in falling edge
  - 1 1 = enables intterupt in rising edge
*/

#define LED  PB4 // pin 12 (PB4)
#define BUTTON PD3 // pin 03 (PD3)

void setup(void) {

  // Disable External Interrupts globally
  cli();

  // LED as output
  DDRB |= LED;

  // Button as input
  DDRD &= ~BUTTON;
  
  // Internal Pull-up
  PORTD |= BUTTON;

  // Enable External Interrupts in INT0  == Pin 2
  EIMSK |= (1 << INT0) 

  // Bits to set mood in INT0
  EICRA |= (1 << ISC01) | (1 << ISC00); 


  // Enable External Interrupts in INT1  == Pin 3
  EIMSK |= (1 << INT1) 

  // Bits to set mood in INT1
  EICRA |= (1 << ISC11) | (1 << ISC10);

  // Enable External Interrupts globally
  sei();
}

/*
  @brief: defines the routine for INT0 interrupt
*/
ISR (INT0_vect) { 
  PORTB ^= LED;
} 


/*
  @brief: defines the routine for INT1 interrupt
*/
ISR (INT1_vect) { 
  PORTB ^= LED;
} 


void loop(void){


}



