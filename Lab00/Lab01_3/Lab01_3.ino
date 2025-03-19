/*
  DDRx = Data direction register ->  (Input = 0 | Output = 1)
  PORTx = P
    - Write data to the pins configured as outputs or to 
      enable internal pull-up resistors for pins configured as inputs.
  PINx = Input Pins Register -> Reads the state of the pins

*/

void setup(void) {
  // set (PORTB3 = Pin 10) as input (button)
  DDRB = DDRB &~ (1 << DDB2); 

  // Keeps the pin HIGH while the button isn't pressed
  PORTB = PORTB | (1 << PB2);

  // set (PORTB3 = Pin 11) as output (LED)
  DDRB = DDRB | (1 << DDB3); 
}

void loop(void) {
  // If the button is pressed (low level, since the pull-up is enabled)
  if (!(PINB & (1 << PB2))){
    PORTB = PORTB | (1 << PB3);  // Turns LED on
  } else {
    PORTB = PORTB &~ (1 << PB3); // Turns LED off
  }
}



