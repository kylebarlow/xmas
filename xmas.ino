    // Christmas Color Changer for 3 Analog LED Strips

    // 2 LED strips with R, G, B LEDS on each, so there are 6 channels to control via FET transistors
    // use the 6 PWM digital I/O pins for the FET gate pins
    #define ledR1 3
    #define ledG1 4
    #define ledB1 5

    #define ledR2 6
    #define ledG2 9
    #define ledB2 10

    #define ledR3 20
    #define ledG3 21
    #define ledB3 22
    
    #define FADESPEED 100 // make this higher to slow down
    #define OFFTIME 900
    #define ONTIME 9000

  // constants won't change. Used here to set pin numbers:
  // Pin 13: Arduino has an LED connected on pin 13
  // Pin 11: Teensy 2.0 has the LED on pin 11
  // Pin  6: Teensy++ 2.0 has the LED on pin 6
  // Pin 13: Teensy 3.0 has the LED on pin 13
  const int ledPin =  13;      // the number of the LED pin

  // Variables will change:
  int ledState = LOW;             // ledState used to set the LED
  long previousMillis = 0;        // will store last time LED was updated

  // the follow variables is a long because the time, measured in miliseconds,
  // will quickly become a bigger number than can be stored in an int.
  long interval = 10000;           // interval at which to blink (milliseconds)
    
    void setup() {
      // set the digital pin as output:
      pinMode(ledPin, OUTPUT);
      //pinMode(ledR1, OUTPUT);
      //pinMode(ledG1, OUTPUT);
      //pinMode(ledB1, OUTPUT);
    }

void led_swap()
{
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
}

void SetPWMValue(byte pin, byte value) {
//  if (value == 0) {
//    digitalWrite(pin,value);
//  } else {
//    analogWrite(pin,value);
//  }
  analogWrite(pin,value);
}
    
    void loop() {
      // set all the LEDs to off
      SetPWMValue(ledR1, 0);
      SetPWMValue(ledG1, 0);
      SetPWMValue(ledB1, 0);
      SetPWMValue(ledR2, 0);
      SetPWMValue(ledG2, 0);
      SetPWMValue(ledB2, 0);
      SetPWMValue(ledR3, 0);
      SetPWMValue(ledG3, 0);
      SetPWMValue(ledB3, 0);
      int i;    
      
      for (i = 0; i < 256; i++) {
        SetPWMValue(ledR1, i);
        SetPWMValue(ledR2, i);
        SetPWMValue(ledR3, i);
        delay(FADESPEED);
      }
      delay(ONTIME);
      led_swap();
      for (i = 0; i < 256; i++) {
        SetPWMValue(ledR1, 255-i);
        SetPWMValue(ledR2, 255-i);
        SetPWMValue(ledR3, 255-i);
        delay(FADESPEED);
      }
      delay(OFFTIME);
      led_swap();
      for (i = 0; i < 256; i++) {
        SetPWMValue(ledG1, i);
        SetPWMValue(ledG2, i);
        SetPWMValue(ledG3, i);
        delay(FADESPEED);
      }
      delay(ONTIME);
      led_swap();
      for (i = 0; i < 256; i++) {
        SetPWMValue(ledG1, 255-i);
        SetPWMValue(ledG2, 255-i);
        SetPWMValue(ledG3, 255-i);
        delay(FADESPEED);
      }
      delay(OFFTIME);
      led_swap();
      for (i = 0; i < 256; i++) {
        SetPWMValue(ledR1, i);
        SetPWMValue(ledG2, i);
        SetPWMValue(ledR3, i);
        delay(FADESPEED);
      }
      delay(ONTIME);
      led_swap();
      for (i = 0; i < 256; i++) {
        SetPWMValue(ledR1, 255-i);
        SetPWMValue(ledG2, 255-i);
        SetPWMValue(ledR3, 255-i);
        delay(FADESPEED);
      }
      delay(OFFTIME);
      led_swap();
      for (i = 0; i < 256; i++) {
        SetPWMValue(ledG1, i);
        SetPWMValue(ledR2, i);
        SetPWMValue(ledG3, i);
        delay(FADESPEED);
      }
      delay(ONTIME);
      led_swap();
      for (i = 0; i < 256; i++) {
        SetPWMValue(ledG1, 255-i);
        SetPWMValue(ledR2, 255-i);
        SetPWMValue(ledG3, 255-i);
        delay(FADESPEED);
      }
      delay(OFFTIME);
      led_swap();
  }
