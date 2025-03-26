/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lab01_6.ino                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:06:16 by smodesto          #+#    #+#             */
/*   Updated: 2025/03/19 22:06:16 by smodesto         ###   ########.fr       */
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
  4. Habilitar interrupção no pino x do registrador
  5. Definir condição de interrupção == mediante a qualquer mudança
  6. Habilitar interrupções globalmente
  7. Definir rotina de interrupção == mudar o estado do led
*/

#define HIGH 1
#define LOW  0
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

  // Enable External Interrupts in INT1  == Pin 3
  EIMSK |= (1 << INT1) 

  // Bits to set mood in INT1 01 = CHANGE
  EICRA |= (0 << ISC11) | (1 << ISC10);

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
  @brief: Checks for a change in the button state before toggling the LED state. 
          Implements a debounce delay to prevent unstable button readings.

  @param CurrentState: The current state of the button (HIGH or LOW).
  @param PrevState: The previous state of the button to detect changes.
  @param PBx: The pin associated with the button (ex:. PB2).

  @return The updated button state after verification and debouncing.
*/


void setup(void) {

}

void loop(void) {

}