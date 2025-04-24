/*
  1. Definir pino x como entrada (Onda quadrada -> 5V, 60Hz)
  2. Definir pino y como saida (Onda atrasada -> 45)
  3. Habilitar interrupção no pino x do registrador
  4. Definir condição de interrupção do pino x == borda de descida
  5. Habilitar interrupções globalmente
  6. Definir variável C responsável por contar os ciclos
  7. Definir rotina de interrupção para x
    7.1 Definir variável estática A responsável por armazenar o tempo inicial
    7.2 Definir variável B responsável por armazenar o tempo atual
    7.3 Verificar se diferença de tempo é menor que 1s
      7.3.1 caso seja, incrementar C

  9. Repetir passos 7 ao 8
*/

#define OUTPUT_PIN    (1 << PB4)  // pin 12 (PB4)
#define INPUT_PIN_2   (1 << PD2)  // pin 2 (PD2)


volatile uint cycles = 0;  // 


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
  Serial.print("Quantidade de ciclos: ");
  Serial.println(cycles);
}

/*
  @brief: defines the routine for INT0 interrupt (INPUT_PIN_2)
*/
ISR(INT0_vect) {
  static uint TimeInit = millis();
  uint CurrentTime = millis();

  if (CurrentTime - TimeInit <= 1000){
    cycles += 1;
  }

}

