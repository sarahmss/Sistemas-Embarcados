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


/*
 1. Definir Periodos T1 e T2
 2. Definir Pino x e y como saida (LED1) (LED2)
 3. Iniciar variavel (Timer) responsável por monitorar o período T2
 4. Colocar x em nivel HIGH 
 5. Esperar metade do periodo T2
 6. Colocar x em nível LOW
 7. Esperar metade do período T2
 8. Verificar se T2 completou 5 periodos
 8.1 Caso 5 periodos tenham sido concluídos, colocar y em nivel HIGH 
 9. Verificar se T2 completou 10 periodos
 9.1 caso 10 periodos tenham sido concluidos, colocar y em nivel LOW e zerar a variavel (Timer)
 10. Repetir passos de 4 a 9
*/

// #define T 1000
// #define T1 2    //  wait T1 = 1/f1 = 1/500 = 2 ms6
#define T 0.4  //  wait T2 = 1/f2 = 1/2500 = 0.4 ms


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
  _delay_ms(T / 2);
  // Half of  period LOW
  PORTB = PORTB & ~(1 << PB5);
  _delay_ms(T / 2);

  // Turn PORTB4 HIGH after  T1/2 =  2.5 * T2 [ms]
  if (Timer >= 2.5) {   
    PORTB = PORTB | (1 << PB4);
  }

  // Turn PORTB4 LOW after  T1/2 = 5 * T2 [ms]
  if (Timer == 5) { 
    PORTB = PORTB & ~(1 << PB4);
    Timer = 0;
  }
  Timer += 1;
}
