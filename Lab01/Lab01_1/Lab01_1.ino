/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lab01_1.ino                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:06:26 by smodesto          #+#    #+#             */
/*   Updated: 2025/03/19 22:06:26 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
  DDRx = Data direction register ->  (Input = 0 | Output = 1)
  PORTx = Write data to the pins configured as outputs or to 
          enable internal pull-up resistors for pins configured as inputs.
  PINx = Input Pins Register -> Reads the state of the pins
  PB5 is associated with pin 13 (connected to an innie led)
  wait T = 1/f = 1/50s = 20ms
*/

void setup(void) {
  // set PORTB5 as a output
  DDRB = DDRB | (1 << DDB5); 
}

void loop(void){
    // Turn led on
    PORTB = PORTB | (1 << PB5);
    delay(10); 
    // Turn led off
    PORTB = PORTB & ~ (1 << PB5);
    delay(10); 

}



