#include "DHT.h"

#define DHTPIN D2     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

#include <FastLED.h>
#define NUM_LEDS 48     //Number of RGB LED beads
#define DATA_PIN D8    //The pin for controlling RGB LED
#define LED_TYPE WS2812B    //RGB LED strip type
CRGB leds[NUM_LEDS];   


void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS); 
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  leds[8] = CRGB (200, 200, 200);
  leds[9] = CRGB (200, 200, 200);
  //leds[8] = CRGB(random(0,255),random(0,255),random(0,255));
  FastLED.show();
  Serial.println("lights up");
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
//heat index = what the temperature feels like to the human body when relative humidity is combined with the air temperature.

  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F("°C |"));
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("% |"));
  Serial.print(F("Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
}
