/*
  DDRx = Data direction register ->  (Input = 0 | Output = 1)
  PORTx = P
    - Write data to the pins configured as outputs or to 
      enable internal pull-up resistors for pins configured as inputs.
  PINx = Input Pins Register -> Reads the state of the pins
*/

#define T     1000
#define T1    2     //  wait T1 = 1/f1 = 1/500s = 2 ms
#define T2    0.4   //  wait T2 = 1/f2 = 1/2500s = 0.4 ms


void setup(void) {
  // set (PORTB5 = Pin 13) as output
  DDRB = DDRB | (1 << DDB5);

  // set (PORTB4 = Pin 12) as output
  DDRB = DDRB | (1 << DDB4); 
}

void loop(void) {
  static uint8_t  Timer = 1;

  PORTB = PORTB | (1 << PB5);
  delay(T/2); 
  PORTB = PORTB & ~ (1 << PB5);
  delay(T/2); 

  if (Timer == 5) {
    PORTB = PORTB | (1 << PB4);
  }
  if (Timer == 10) {
    PORTB = PORTB & ~ (1 << PB4);
    Timer = 0;
  }
  Timer += 1;
}



