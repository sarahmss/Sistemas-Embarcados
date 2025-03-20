/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lab01_2.ino                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:06:40 by smodesto          #+#    #+#             */
/*   Updated: 2025/03/19 22:06:40 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
  DDRx = Data direction register ->  (Input = 0 | Output = 1)
  PORTx = Write data to the pins configured as outputs or to 
          enable internal pull-up resistors for pins configured as inputs.
  PINx = Input Pins Register -> Reads the state of the pins
*/

// #define T 1000
#define T1 2    //  wait T1 = 1/f1 = 1/500s = 2 ms
#define T2 0.4  //  wait T2 = 1/f2 = 1/2500s = 0.4 ms


void setup(void) {
  // set (PORTB5 = Pin 13) as output
  DDRB = DDRB | (1 << DDB5);

  // set (PORTB4 = Pin 12) as output
  DDRB = DDRB | (1 << DDB4);
}

void loop(void) {
  static uint8_t Timer = 1;

  // Half of  period HIGH
  PORTB = PORTB | (1 << PB5);
  delay(T2 / 2);
  // Half of  period LOW
  PORTB = PORTB & ~(1 << PB5);
  delay(T2 / 2);

  // Turn PORTB4 HIGH after  T1 =  5 * T2 [ms]
  if (Timer == 5) {   
    PORTB = PORTB | (1 << PB4);
  }

  // Turn PORTB4 LOW after 2 * T1 = 10 * T2 [ms]
  if (Timer == 10) { 
    PORTB = PORTB & ~(1 << PB4);
    Timer = 0;
  }
  Timer += 1;
}
