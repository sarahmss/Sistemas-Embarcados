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
  1. Definir pino x como entrada (Temporizador 555 = 5KHz --> 200us)
  3. Definir pino y como saida (Onda gerada = 10Hz --> 0.1s)
  4. Habilitar interrupção no pino x do registrador
  5. Definir condição de interrupção == borda de descida
  6. Habilitar interrupções globalmente
  7. Definir rotina de interrupção 
    7.1 Verificar 
*/


#define T 100                  // 0.1s = 100ms
#define OUTPUT_PIN  (1 << PB4) // pin 12 (PB4)
#define INPUT_PIN   (1 << PD3) // pin 3 (PD3)

void setup(void) {
  // Serial.begin(2000000);


  // Disable External Interrupts globally
  cli();

  // OUTPUT_PIN as output
  DDRB |= OUTPUT_PIN;

  // INPUT_PIN as input
  DDRD &= ~INPUT_PIN;
  
  // Internal Pull-up
  PORTD |= INPUT_PIN;

  // Enable External Interrupts in INT1  == Pin 3
  EIMSK |= (1 << INT1); 

  // Bits to set mode in INT1 10 = Falling
  EICRA |=  (1 << ISC11);  // Set ISC11
  EICRA &= ~(1 << ISC10);  // Clear ISC10
  
  // Enable External Interrupts globally
  sei();
}

/*
  @brief: defines the routine for INT1 interrupt
*/
ISR(INT1_vect) {
  static uint16_t Counter = 1;

  if (Counter == 250){
    PORTB ^= OUTPUT_PIN;
    _delay_ms(T/2);
    Counter = 1;
  }
  Counter += 1;
}


void loop(void) {
  // int Timer = analogRead(A0);
  // int Out = analogRead(A1);

  // Serial.print("Timer: "); Serial.println(Timer);
  // Serial.print("Output: ");Serial.println(Out);
}