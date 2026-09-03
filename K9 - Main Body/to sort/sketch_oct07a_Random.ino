//  12 LED, 6 LED max Random flasher for K9 by Mathew Prentis
//  Tested on Arduino UNO V3 Sept 2014 
//  12 LED's to pins 1,2,3,4,5,6,7,8,9,10,11,12
//  limit LED current with 220R resistor on each LED.
//  Pin to LED starting Top Left hand corner
//     pin 1, 2, 3, 4    top row of LEDS
//     pin 5, 6, 7, 8    middle row of LEDs
//     pin 9, 10, 11, 12 bottom row of LEDs
//     pin GND common to all LEDs Cathodes
//     pins 0 and 13 not connected.

int ranNum1;
int ranNum2;
int ranNum3;
int ranNum4;
int ranNum5;
int ranNum6;
int ranDel;

void setup() {
//randomSeed for Random Number Generator (K9 first TV appearance)
randomSeed(2020);
// Setup 12 output ports for LED's
pinMode(0, OUTPUT);
pinMode(1, OUTPUT);
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);
pinMode(12, OUTPUT);

//Power up

//digitalWrite(0, HIGH);
//delay (1000);
//digitalWrite(0, LOW);

digitalWrite(1, HIGH);
delay (1000);
digitalWrite(1, LOW);
digitalWrite(2, HIGH);
delay (1000);
digitalWrite(2, LOW);
digitalWrite(3, HIGH);
delay (1000);
digitalWrite(3, LOW);
digitalWrite(4, HIGH);
delay (1000);
digitalWrite(4, LOW);
digitalWrite(5, HIGH);
delay (1000);
digitalWrite(5, LOW);
digitalWrite(6, HIGH);
delay (1000);
digitalWrite(6, LOW);
digitalWrite(7, HIGH);
delay (1000);
digitalWrite(7, LOW);
digitalWrite(8, HIGH);
delay (1000);
digitalWrite(8, LOW);
digitalWrite(9, HIGH);
delay (1000);
digitalWrite(9, LOW);
digitalWrite(10, HIGH);
delay (1000);
digitalWrite(10, LOW);
digitalWrite(11, HIGH);
delay (1000);
digitalWrite(11, LOW);
digitalWrite(12, HIGH);
delay (1000);
digitalWrite(12, LOW);

// start up display
// letter K
  digitalWrite(1, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(11, HIGH);
  delay (4000);
  digitalWrite(1, LOW);
  digitalWrite(5, LOW);
  digitalWrite(9, LOW);
  digitalWrite(6, LOW);
  digitalWrite(3, LOW);
  digitalWrite(11, LOW);
  delay (1000);

// number 9
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(12, HIGH);
  delay (4000);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  delay (1000);
  
}
void loop() { 
    //Generate random number between 1 and 20
    //more numbers than LEDS so 6 LED's not on all the time
    ranNum1=random(1,20);
    ranNum2=random(1,20);
    ranNum3=random(1,20);
    ranNum4=random(1,20);
    ranNum5=random(1,20); 
    ranNum6=random(1,20);
    
    //Trim random number to 12. Pin 0 not used.
    if (ranNum1 > 12){
      ranNum1 = 0;
    }
      if (ranNum2 > 12){
      ranNum2 = 0;
    }
    if (ranNum3 > 12){
      ranNum3 = 0;
    }
    if (ranNum4 > 12){
      ranNum4 = 0;
    }
     if (ranNum5 > 12){
      ranNum5 = 0;
    }
     if (ranNum6 > 12){
      ranNum6 = 0;
    }
    
    // Generate random delay time
    ranDel=random(50,1000);
    
    //Turn on the LED's
    digitalWrite(ranNum1, HIGH);
    digitalWrite(ranNum2, HIGH);
    digitalWrite(ranNum3, HIGH);
  
    delay(ranDel);
    //Turn off the LED's
    digitalWrite(ranNum1, LOW);
    digitalWrite(ranNum2, LOW);
    digitalWrite(ranNum3, LOW);
 
}
