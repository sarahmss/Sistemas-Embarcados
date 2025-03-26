/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lab01_5.ino                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:07:59 by smodesto          #+#    #+#             */
/*   Updated: 2025/03/19 22:07:59 by smodesto         ###   ########.fr       */
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
  2. Não configurar Pull-up (Colocar o pino inicialmente em estado HIGH)
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
# define HIGH 1
# define LOW  0

void setup(void) {
  // set (PORTB3 = Pin 10) as input (button)
  DDRB &= ~(1 << DDB2); 

  // Keeps the pin HIGH while the button isn't pressed
  // PORTB |=  (1 << PB2);

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



