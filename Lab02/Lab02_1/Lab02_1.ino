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
  1. Definir pino x como entrada (Botão)
  2. Configurar Pull-up (Colocar o pino inicialmente em estado HIGH)
  3. Definir pino y como saida (LED)
  4. Habilitar interrupção no pino x do registrador
  5. Definir condição de interrupção == mediante a qualquer mudança
  6. Habilitar interrupções globalmente
  7. Definir rotina de interrupção == mudar o estado do led
*/

#define LED    (1 << PB4)  // pin 12 (PB4)
#define BUTTON (1 << PD3)  // pin 3 (PD3)

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
  EIMSK |= (1 << INT1); 

  // Bits to set mode in INT1 01 = CHANGE
  EICRA &= ~(1 << ISC11);  // Clear ISC11
  EICRA |=  (1 << ISC10);  // Set ISC10
  
  // Enable External Interrupts globally
  sei();
}

/*
  @brief: defines the routine for INT0 interrupt
*/
ISR(INT1_vect) {
  PORTB ^= LED; // Toggle LED
}


void loop(void) {

}