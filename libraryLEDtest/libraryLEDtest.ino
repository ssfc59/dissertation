#include <FastLED.h>
#define NUM_LEDS 48     //Number of RGB LED beads
#define DATA_PIN D8    //The pin for controlling RGB LED
#define LED_TYPE WS2812B    //RGB LED strip type
CRGB leds[NUM_LEDS];    //Instantiate RGB LED

const int libHumidity = 50;
const int areaHumidity = 66;

void setup() { 
  Serial.begin(115200);
   FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);     //Initialize RGB LED
}

void loop() {
  int display = areaHumidity - libHumidity;
  //display = 16!
  Serial.println(display);



        for (int i =41 ; i <= 43; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }

    //28 36 less
//40- 43 lights up 45+ rn

  delay(5000);

}

/*
   for (int i = 7; i <= 9; i++) {
    leds[i] = CRGB (100, 100, 100);
    FastLED.show();
    }
  
  for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(0,100,0);
      FastLED.show();
      delay(500);
  }

    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i]= CRGB (255, 255, 255);
  }
 
  */

/*
  leds[0] = CRGB::Red;     //LED shows red light
  FastLED.show();
  delay(1000);
  leds[0] = CRGB::Green;    //LED shows green light
  FastLED.show();
  delay(1000);
  leds[0] = CRGB::Blue;     // LED shows blue light
  FastLED.show();
  delay(1000);
  leds[0] = CRGB(random(0,255),random(0,255),random(0,255));    // LED shows a randomly mixed color
  FastLED.show();
  delay(1000);
  */
