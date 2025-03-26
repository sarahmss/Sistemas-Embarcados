/*
  DDRx = Data direction register ->  (Input = 0 | Output = 1)
  PORTx = 
    - Write data to the pins configured as outputs or to 
      enable internal pull-up resistors for pins configured as inputs.
  PINx = Input Pins Register ->
*/

void setup(void) {
  // set PORTB5 as a output
  DDRB = DDRB | (1 << DDB5); 
}

// PB5 is associated with pin 13 (connected to an innie led)
// wait T = 1/f = 1/50s = 20ms

void loop(void){
    // Turn led on
    PORTB = PORTB | (1 << PB5);
    delay(20); 
    // Turn led off
    PORTB = PORTB & ~ (1 << PB5);
    delay(20); 

}



