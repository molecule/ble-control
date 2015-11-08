//******** Neopixel *********** //
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define NEOPIXEL_PIN 4
#define NUM_LEDS 4
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
int delayVal = 50;

uint32_t hot_pink      = strip.Color(48, 0, 24);
uint32_t light_blue    = strip.Color(0, 24, 24);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Neopixel setup
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {
  // put your main code here, to run repeatedly:
  String color = readFromBluetooth();
  if (color==String("p")) {
    chasePersist(NUM_LEDS, hot_pink);
  }
  if (color==String("b")) {
    chasePersist(NUM_LEDS, light_blue);
  }
}

/**
 * Read the data from the BLE, breaking on '\n' and '\r' characters.
 */
String readFromBluetooth() {
  String readString = "";
  
    while (Serial.available()) {
    delay(10);  //small delay to allow input buffer to fill

    char c = Serial.read(); //gets one byte from serial buffer
    if (c == '\n' || c == '\r') {
      break;
    }
    readString += c;
  } 
  return readString;
}

static void chasePersist(int numPixels, uint32_t c) {
 for(int i=0;i<numPixels;i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, c);
    strip.show(); // This sends the updated pixel color to the hardware.
    delay(delayVal); // Delay for a period of time (in milliseconds).
  } 
}
