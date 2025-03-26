/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lab01_3.ino                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:07:31 by smodesto          #+#    #+#             */
/*   Updated: 2025/03/19 22:07:31 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
  DDRx = Data direction register ->  (Input = 0 | Output = 1)
  PORTx = Write data to the pins configured as outputs or to 
          enable internal pull-up resistors for pins configured as inputs.
  PINx = Input Pins Register -> Reads the state of the pins
*/


/*
  1. Definir pino x como entrada (Botão)
  2. Configurar Pull-up (Colocar o pino inicialmente em estado HIGH)
  3. Definir pino y como saida (LED)
  4. Verificar se há alteração no estado do pino x
  4.1 Caso o pino esteja en nível LOW, colocar o pino y em nível HIGH
  4.2 caso o pino esteja em nível HIGH, colocar o pino y em nível LOW
*/

void setup(void) {
  // set (PORTB2 = Pin 10) as input (button)
  DDRB = DDRB &~ (1 << DDB2); 

  // Keeps the pin HIGH while the button isn't pressed
  PORTB = PORTB | (1 << PB2);

  // set (PORTB3 = Pin 11) as output (LED)
  DDRB = DDRB | (1 << DDB3); 
}

void loop(void) {
  // Checks state of PORTB2, LOW means that button 
  // is pressed and LED should be turned on (Pull-up)
  if (!(PINB & (1 << PB2))) {
    PORTB = PORTB | (1 << PB3);  // Turns LED on
  }
  // HIGH means that button isn't pressed and LED should be turned off 
  else { 
    PORTB = PORTB &~ (1 << PB3); // Turns LED off
  }
}



