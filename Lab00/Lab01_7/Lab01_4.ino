/*
  DDRx = Data direction register ->  (Input = 0 | Output = 1)
  PORTx = P
    - Write data to the pins configured as outputs or to 
      enable internal pull-up resistors for pins configured as inputs.
  PINx = Input Pins Register ->

*/
# define HIGH 1
# define LOW  0

void setup(void) {
  // set (PORTB3 = Pin 10) as input (button)
  DDRB = DDRB &~ (1 << DDB2); 

  // Keeps the pin HIGH while the button isn't pressed
  PORTB = PORTB | (1 << PB2);

  // set (PORTB3 = Pin 11) as output (LED)
  DDRB = DDRB | (1 << DDB3); 
}

void loop(void) {

  static uint8_t PrevState = 1;
  uint8_t        CurrentState = !(PINB & (1 << PB2)); 
  
  if (CurrentState != PrevState) {        // Checks changes of state

    delay(50);                            // Debouncing
    CurrentState = !(PINB & (1 << PB2));  // Re-reading

    if (CurrentState == HIGH){
      PORTB = PORTB ^ (1 << PB3); // Switchs LED state when button is pressed
    }
    PrevState = CurrentState;
  }
}



