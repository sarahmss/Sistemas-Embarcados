/*
  DDRx = Data direction register ->  (Input = 0 | Output = 1)
  PORTx = P
    - Write data to the pins configured as outputs or to 
      enable internal pull-up resistors for pins configured as inputs.
  PINx = Input Pins Register -> Reads the state of the pins
*/

#define HIGH 1
#define LOW  0

uint8_t ChangeState(uint8_t CurrentState, uint8_t PrevState, uint8_t PBx) {
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
