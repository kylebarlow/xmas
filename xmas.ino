// Christmas Color Changer for 3 Analog LED Strips

#include <FastLED.h>

// 3 LED strips with R, G, B LEDS on each, so there are 9 channels to control via FET transistors
// use the PWM digital I/O pins for the FET gate pins
#define ledR1 3
#define ledG1 4
#define ledB1 5

#define ledR2 6
#define ledG2 9
#define ledB2 10

#define ledR3 20
#define ledG3 21
#define ledB3 22
    
#define FADESPEED 30 // make this higher to slow down
#define OFFTIME 400
#define ONTIME 12000

// constants won't change. Used here to set pin numbers:
// Pin 13: Arduino has an LED connected on pin 13
// Pin 11: Teensy 2.0 has the LED on pin 11
// Pin  6: Teensy++ 2.0 has the LED on pin 6
// Pin 13: Teensy 3.0 has the LED on pin 13
const int ledPin = 13; // the number of the LED pin

const int numStrips = 3;

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 10000;           // interval at which to blink (milliseconds)
    
void showAnalogRGB( const int strip_num, const CRGB& rgb)
{
  if ( strip_num == 0 ) {
    analogWrite(ledR1,   rgb.r );
    analogWrite(ledG1, rgb.g );
    analogWrite(ledB1,  rgb.b );
  } else if ( strip_num == 1 ) {
    analogWrite(ledR2,   rgb.r );
    analogWrite(ledG2, rgb.g );
    analogWrite(ledB2,  rgb.b );
  } else if ( strip_num == 2 ) {
    analogWrite(ledR3,   rgb.r );
    analogWrite(ledG3, rgb.g );
    analogWrite(ledB3,  rgb.b );
  }
}

void showAnalogRGBs( boolean led_strips[], const CRGB& rgb)
{
  int i;
  for (i = 0; i < numStrips; i++) {
    if ( led_strips[i] ) {
      showAnalogRGB(i, rgb);
    }
  }
}

void all_off()
{
  boolean all_strips[] = {true, true, true};
  showAnalogRGBs( all_strips, CRGB::Black );
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
  analogWrite(pin,value);
}

// colorBars: flashes Red, then Green, then Blue, then Black.
// Helpful for diagnosing if you've mis-wired which is which.
void colorBars()
{
  boolean all_strips[] = {true, true, true};
  showAnalogRGBs( all_strips, CRGB::Red );   delay(500);
  showAnalogRGBs( all_strips, CRGB::Green ); delay(500);
  showAnalogRGBs( all_strips, CRGB::Blue );  delay(500);
  showAnalogRGBs( all_strips, CRGB::Black ); delay(500);
  showAnalogRGBs( all_strips, CRGB::White ); delay(500);
  showAnalogRGBs( all_strips, CRGB::Black ); delay(500);
}

void slow_xmas_fade() {
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

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(ledR1, OUTPUT);
  pinMode(ledG1, OUTPUT);
  pinMode(ledB1, OUTPUT);
  pinMode(ledR2, OUTPUT);
  pinMode(ledG2, OUTPUT);
  pinMode(ledB2, OUTPUT);
  pinMode(ledR3, OUTPUT);
  pinMode(ledG3, OUTPUT);
  pinMode(ledB3, OUTPUT);
  
  // Flash the "hello" color sequence: R, G, B, black.
  colorBars();
}

void rainbow(int num_rainbow_loops) 
{
  boolean all_strips[] = {true, true, true};
  int hue;
  int i;
  for (i = 0; i < num_rainbow_loops; i++) {
    for (hue = 0; hue < 256; hue++) {
      hue = hue + 1;
      // Use FastLED automatic HSV->RGB conversion
      showAnalogRGBs( all_strips, CHSV( hue, 255, 255) );
      delay(20);
    }
  }
}

void xmas_run(const int outer_loops)
{
  all_off();
  const int delay_time = 800;
  int i;
  int j;
  for (j = 0; j < outer_loops; j++) {
    for (i = 0; i < numStrips; i++) {
      showAnalogRGB( i, CRGB::Red ); delay(delay_time);
    }
    for (i = 0; i < numStrips; i++) {
      showAnalogRGB( i, CRGB::Green ); delay(delay_time);
    }
    for (i = 0; i < numStrips; i++) {
      showAnalogRGB( i, CRGB::Black ); delay(delay_time);
    }
  }
}

void random_xmas(const int switches)
{
  all_off();
  int i;
  int led_strip;
  int color_i;
  for (i = 0; i < switches; i++) {
    led_strip = random(0, numStrips);
    color_i = random(0, 100);
    if (color_i < 45) {
      showAnalogRGB( led_strip, CRGB::Red );
    } else if (color_i < 90) {
      showAnalogRGB( led_strip, CRGB::Green );
    } else {
      showAnalogRGB( led_strip, CRGB::Black );
    }
    delay(500);
  }
}

void cal_flash(int switches)
{
  all_off();
  int i;
  int led_strip;
  int color_i;
  for (i = 0; i < switches; i++) {
    showAnalogRGB( 0, CHSV( 152, 255, 77 ) );
    showAnalogRGB( 2, CHSV( 152, 255, 77 ) );
    showAnalogRGB( 1, CHSV( 33, 232, 252 ) );
    delay(500);
    showAnalogRGB( 1, CHSV( 152, 255, 77 ) );
    showAnalogRGB( 0, CHSV( 33, 232, 252 ) );
    showAnalogRGB( 2, CHSV( 33, 232, 252 ) );
    delay(500);
  }
}
    
void loop()
{
  cal_flash(50);
  rainbow(5);
  xmas_run(3);
  random_xmas(100);
  slow_xmas_fade();
}

