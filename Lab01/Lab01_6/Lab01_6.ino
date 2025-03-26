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
  4. Definir uma variável z para armazenar o estado anterior
    4.1 Atribuir a ela nível HIGH (pull-up) 
  5. Definir uma variável w para armazenar o estado atual
    5.1 Atribuir a ela a leitura do pino x
  6. Comparar o estado anterior com o estado atual 
  7. Caso haja mudança de estado, aplicar um delay para evitar efeito bouncing
  8. Fazer a re-leitura do estado atual e armazenar em w
  9. Verificar se há mudança de estado é mantida
  9.1 Alternar o estado do pino  y mediante a mudança 
  10. repetir passos 6 ao 9
*/

#define HIGH 1
#define LOW  0

/*
  @brief: Checks for a change in the button state before toggling the LED state. 
          Implements a debounce delay to prevent unstable button readings.

  @param CurrentState: The current state of the button (HIGH or LOW).
  @param PrevState: The previous state of the button to detect changes.
  @param PBx: The pin associated with the button (ex:. PB2).

  @return The updated button state after verification and debouncing.
*/
uint8_t ChangeState(uint8_t CurrentState, uint8_t PrevState, uint8_t PBx)
{  
  if (CurrentState != PrevState) {        // Checks changes of state
    _delay_ms(50);                        // Debouncing
    CurrentState = !(PINB & (1 << PBx));  // Re-reading

    if (CurrentState == HIGH) {
      PORTB ^= (1 << PB3);                // Toggle LED state
    }
  }
  return CurrentState;
}

void setup(void) {
  // Set PB1 (Pin 9) as input (button)
  DDRB &= ~(1 << DDB1);
  PORTB |= (1 << PB1);  // Enable internal pull-up

  // Set PB2 (Pin 10) as input (button)
  DDRB &= ~(1 << DDB2);
  PORTB |= (1 << PB2);  // Enable internal pull-up

  // Set PB3 (Pin 11) as output (LED)
  DDRB |= (1 << DDB3);
}

void loop(void) {
  static uint8_t PrevStateB1 = HIGH;
  uint8_t CurrentStateB1 = !(PINB & (1 << PB1)); 

  static uint8_t PrevStateB2 = HIGH;
  uint8_t CurrentStateB2 = !(PINB & (1 << PB2)); 

  PrevStateB1 = ChangeState(CurrentStateB1, PrevStateB1, PB1);
  PrevStateB2 = ChangeState(CurrentStateB2, PrevStateB2, PB2);
}
