/*
  1. Definir pino x como entrada (Onda quadrada -> 5V, 60Hz)
  2. Definir pino y como saida (Onda atrasada -> 45)
  3. Habilitar interrupção no pino x do registrador
  4. Definir condição de interrupção do pino x == borda de descida
  5. Habilitar interrupções globalmente
  6. Definir variável A global responsável por formar a saida do arduino
  7. Definir rotina de interrupção para x
    7.1 Alterar o estado de A a cada interrupção
  8. Verificar se o estado de A foi alterado
    8.1 Caso tenha sido,  defasar o Periodo T equivalente (45° ou 5°)
    8.2 Alterar o estado do pino y
  9. Repetir passos 7 ao 8
*/

#define OUTPUT_PIN    (1 << PB4)  // pin 12 (PB4)
#define INPUT_PIN_2   (1 << PD2)  // pin 2 (PD2)
#define T_45 		      1.041625 	  // Period 
#define T_5 		      0.1157 	    // Period 

volatile uint8_t Mood = 0;  // False is 0, True is 1


void setup(void) {
  Serial.begin(9600);
  // Disable External Interrupts globally
  cli();

  // set OUTPUT_PIN as output
  DDRB |= OUTPUT_PIN;
  
  // set INPUT_PIN_2 as input
  DDRD &= ~INPUT_PIN_2;

  // Enable External Interrupts in INT0  == Pin 2
  EIMSK |= (1 << INT0);

  // Bits to set mode in INT0 01 = CHANGE
  EICRA &= ~(1 << ISC01);  // Clear ISC01
  EICRA |=  (1 << ISC00);  // Set ISC00


  // Enable External Interrupts globally
  sei();
}

void loop(void) {
  if (Mood == 1){
      _delay_ms(T_45);	

      PORTB ^= OUTPUT_PIN;
      _delay_ms(100);	
      PORTB ^= OUTPUT_PIN;

      Mood = 0;
      Serial.println("Entrou 1");  
  }
}

/*
  @brief: defines the routine for INT0 interrupt (INPUT_PIN_2)
*/
ISR(INT0_vect) {
  Mood = 1;
}

