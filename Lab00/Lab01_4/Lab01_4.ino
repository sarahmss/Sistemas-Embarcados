/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lab01_4.ino                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:07:45 by smodesto          #+#    #+#             */
/*   Updated: 2025/03/19 22:07:45 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
  DDRx = Data direction register ->  (Input = 0 | Output = 1)
  PORTx = Write data to the pins configured as outputs or to 
          enable internal pull-up resistors for pins configured as inputs.
  PINx = Input Pins Register -> Reads the state of the pins
*/

# define HIGH 1
# define LOW  0

void setup(void) {
  // set (PORTB3 = Pin 10) as input (button)
  DDRB &= ~(1 << DDB2); 

  // Keeps the pin HIGH while the button isn't pressed
  PORTB |= (1 << PB2);

  // set (PORTB3 = Pin 11) as output (LED)
  DDRB |= (1 << DDB3); 
}

void loop(void) {

  static uint8_t PrevState = HIGH;
  uint8_t        CurrentState = !(PINB & (1 << PB2)); 
  
  if (CurrentState != PrevState) {        // Checks changes of state

    delay(50);                            // Debouncing
    CurrentState = !(PINB & (1 << PB2));  // Re-reading

    if (CurrentState == HIGH){
      PORTB = PORTB ^ (1 << PB3);         // Toggle LED state
    }
    PrevState = CurrentState;
  }
}



