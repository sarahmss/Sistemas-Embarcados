/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lab02_3.ino                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:06:16 by smodesto          #+#    #+#             */
/*   Updated: 2025/03/19 22:06:16 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
  0. Definir variavel global B responsavel por armazenar o estado
  1. Definir pino x como entrada (Temporizador 555 = 5KHz --> 200us)
  2. Definir pino y como entrada (Botão)
  3. Definir pino z como saida (Onda gerada = 1000Hz --> 1.0 ms | 500Hz --> 0.5 ms | 250Hz --> 0.25 ms)
  4. Habilitar interrupção no pino x do registrador
  5. Habilitar interrupção no pino y do registrador
  6. Definir condição de interrupção do pino x == borda de descida
  7. Definir condição de interrupção do pino y == borda de descida 
  8. Habilitar interrupções globalmente
  9. Definir rotina de interrupção para x
    9.1 Definir variavel A responsável por contar
    9.2 Verificar se A atingiu o valor esperado == B
      9.2.1 Caso tenha atingido, alterar o estado da porta 
    9.3 Incrementar A a cada interrupção
  10. Definir rotina de interrupção para y
    10.1 Definir variavel C responsável por salvar o estado do botão
    10.2 Verificar alteração no estado do botão
      10.2.1 Caso haja alteração, mudar a variável B para o esta correspondente
*/

#define OUTPUT_PIN    (1 << PB4)  // pin 12 (PB4)
#define INPUT_PIN_3   (1 << PD3)  // pin 3 (PD3)
#define INPUT_PIN_2   (1 << PD2)  // pin 2 (PD2)

typedef enum e_state
{
  F_1000 = 5,
  F_500 = 11,  // 2.5
  F_250 = 21   // 1.5
} t_state;

volatile t_state State = F_1000;
volatile uint8_t Mood = 0;  // False is 0, True is 1

void setup(void) {
  .begin(9600);
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
  @brief: defines the routine for INT1 interrupt (INPUT_PIN_3)
*/
ISR(INT1_vect) {
  static uint16_t Counter = 1;

  if (Counter == State){
    PORTB ^= OUTPUT_PIN;
    Counter = 1;
  }
  Counter += 1;
}

/*
  @brief: defines the routine for INT0 interrupt (INPUT_PIN_2)
*/
ISR(INT0_vect) {
  static bool Mood = false;

  if (!Mood){
    State = F_500;
    Mood = true;
  }
  
  else if (Mood){
    State = F_250;
    Mood = false;
  }
}

void loop(void) {

}
