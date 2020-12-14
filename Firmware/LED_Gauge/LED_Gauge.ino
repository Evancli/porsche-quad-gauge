#include <Arduino.h>

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED_PIN 14
#define LIGHT_SENSE A1
#define FUEL_SENSE 16
#define ALTERNATOR_SENSE 17
#define OIL_SENSE 18
#define BRAKE_SENSE 19

#define MAX_BRIGHTNESS 128

#define LED_COUNT 12

// Ref: https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800);

int lightSenseValue = 0;
int fuelSenseValue = 0;
int alternatorSenseValue = 0;
int oilSenseValue = 0;
int brakeSenseValue = 0;

int brightnessValue = 0;

/// RGBW seems to be GRBW
uint32_t fuelColor = leds.Color(128, 255, 0, 0); // leds.Color(255, 128, 0, 0);
uint32_t alternatorColor = leds.Color(0, 255, 0, 0);
uint32_t oilColor = leds.Color(255, 0, 0, 0);
uint32_t brakeColor = leds.Color(0, 255, 0, 0);

void setup() {

  pinMode(FUEL_SENSE, INPUT);
  pinMode(ALTERNATOR_SENSE, INPUT);
  pinMode(OIL_SENSE, INPUT);
  pinMode(BRAKE_SENSE, INPUT);

  leds.setBrightness(MAX_BRIGHTNESS);

  leds.begin();
  leds.show();
}

void loop() {

  lightSenseValue = analogRead(LIGHT_SENSE);
  fuelSenseValue = digitalRead(FUEL_SENSE);
  alternatorSenseValue = digitalRead(ALTERNATOR_SENSE);
  oilSenseValue = digitalRead(OIL_SENSE);
  brakeSenseValue = digitalRead(BRAKE_SENSE);



  brightnessValue = map(lightSenseValue, 0, 1023, 0, 128);



  for (int i = 0; i < LED_COUNT; i++) {
    leds.setPixelColor(i, leds.Color(0, 0, 0, brightnessValue));

    if (i >= 0 && i < 3 && oilSenseValue) {
      leds.setPixelColor(i, oilColor );
    }

    if (i >= 3  && i < 6 && fuelSenseValue) {
      leds.setPixelColor(i, fuelColor );
    }

    if (i >= 6 && i < 9 && alternatorSenseValue) {
      leds.setPixelColor(i, alternatorColor);
    }

    if (i >= 9 && i < 12 && brakeSenseValue) {
      leds.setPixelColor(i, brakeColor);
    }
  }


//  for (int i = 0; i < 24; i++) {
//    if (i < brightness) {
//      leds.setPixelColor(i, leds.Color(255, 0, 0));
//    } else {
//      leds.setPixelColor(i, leds.Color(0, 0, 0));
//    }
//  }

  leds.show();
  delay(50);
}
