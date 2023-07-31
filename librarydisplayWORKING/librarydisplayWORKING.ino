#include <ArduinoJson.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

//ezTime library
#include <ezTime.h>
Timezone myTimezone;
int startHour = 8;    // Start hour (24-hour format)
int endHour = 20;

// LEDS
#include <FastLED.h>
#define NUM_LEDS 192     //Number of RGB LED beads
#define DATA_PIN D8    //The pin for controlling RGB LED
#define LED_TYPE WS2812B    //RGB LED strip type
CRGB leds[NUM_LEDS];    //Instantiate RGB LED

// DHT
#include "DHT.h"
#define DHTPIN D3    // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#include "arduino_secrets.h";

void setup() 
{
// init serial
  Serial.begin(115200);
  
//init LEDs
  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS); 
  Serial.println();
  
//init DHT
  dht.begin();
  //should I wake it up for a few more seconds?
   Serial.println("wake DHT up for 5 seconds");
   delay(5000);
  
 //init WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
      for (int i = 0; i < NUM_LEDS; i++) {
    leds[i]= CRGB (255, 0, 0);
  }
    delay(1000);
  }
  FastLED.clear();
  Serial.println(WiFi.localIP());
    waitForSync();
myTimezone.setPosix("GMT0BST,M3.5.0/1,M10.5.0");
}

void loop () {
  /////////////////////////////////
 // 1. Make secured Get Request //
/////////////////////////////////


  int currentHour = myTimezone.hour();
 Serial.println("Current Hour is ");
 Serial.print(currentHour);
 Serial.println(":00");
  if (currentHour >= startHour && currentHour < endHour) {
WiFiClientSecure *client = new WiFiClientSecure;
// set secure client without certificate
client->setInsecure();
//create an HTTPClient instance
HTTPClient https;

https.begin(*client, APIurl);
Serial.print("[HTTPS] GET...\n");
https.addHeader("X-IBM-Client-Id", clientId);
https.addHeader("X-IBM-Client-Secret", clientSecret);
https.setTimeout(5000);
int httpCode = https.GET();

if (httpCode <= 0) {
  Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    Serial.println(F("Error on API request"));
  }
else {
String payload = https.getString();

//Parse response
DynamicJsonDocument doc(49152); //memory is made to be used :))
DeserializationError error = deserializeJson(doc, payload);

  // Test if parsing succeeds
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  } 

//fetch and store values
 float Temperature = doc["features"][0]["properties"]["timeSeries"][2]["screenTemperature"];
 float Humidity = doc["features"][0]["properties"]["timeSeries"][2]["screenRelativeHumidity"];
 float HeatIndex = doc["features"][0]["properties"]["timeSeries"][2]["feelsLikeTemperature"];
 
//print values
  Serial.print(F("Outside temperature: ")); 
  Serial.print(Temperature); 
  Serial.print(F(" | Outside humidity: "));
  Serial.print(Humidity);
  Serial.print(F(" | Ambient temperature: "));
  Serial.print(HeatIndex);
  Serial.println();

  //////////////////////////
 // 2. Obtain DHT values //
//////////////////////////

  // Reading temperature, humidity and heat index
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float hic = dht.computeHeatIndex(t, h, false);
  //heat index = what the temperature feels like to the human body when relative humidity is combined with the air temperature.
  //false so it returns values in degrees Celsius

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)|| isnan(hic)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    Serial.println(F("2 minutes to debug..."));
     delay(120000);
    return;
  }
  
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F("°C |"));
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("% |"));
  Serial.print(F(" Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.println();

  ///////////////////////////////////
 // 3. Compare DHT and API values //
///////////////////////////////////

   int tempdisplay = t - Temperature;
   Serial.print(F("tempdisplay = "));
      Serial.print(tempdisplay);
      Serial.print(F("°C"));
      Serial.println();

  int humiditydisplay = h - Humidity;
  Serial.print(F("humiditydisplay = "));
      Serial.print(humiditydisplay);
      Serial.print(F("°C"));
      Serial.println(); 

  ////////////////////////////////////////////
 //  4. Light up corresponding LED lights  //
////////////////////////////////////////////
 FastLED.clear();
if (tempdisplay <= 0) {
    //COOLER INSIDE THE LIBRARY
       for (int i = 92; i <= 102; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    }
    else if (tempdisplay > 0) {
    //WARMER INSIDE THE LIBRARY
       for (int i = 109; i <= 120; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
      }
switch (tempdisplay){
   case 0:
     for (int i = 188; i <= 192; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 0
    
   case -1:
   case 1:
     for (int i = 183; i <= 186; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 1

   case -2:
   case 2:
     for (int i = 179; i <= 181; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 2

   case -3:
   case 3:
     for (int i = 174; i <= 176; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 3
 
   case -4:
   case 4:
     for (int i = 169; i <= 170; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 4  
    
    case -5:
    case 5:
     for (int i = 128; i <= 132; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 5
     
    case -6:
    case 6:
     for (int i = 133; i <= 135; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 6
    
   case -7:
   case 7:
     for (int i = 138; i <= 140; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 7

    case -8:
    case 8:
     for (int i = 143; i <= 145; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 8

    case -50 ... -9:
    case 9 ... 50:
     for (int i = 148; i <= 151; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 9+

   default:
      for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(100,100,0); //yellow
      FastLED.show();
  }
      Serial.print("Sensor error");
  }

 if (humiditydisplay <= 0) {
  //LESS HUMID
   for (int i = 13; i <= 19; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
 }
   else if (humiditydisplay > 0){
    //MORE HUMID
     for (int i = 1; i <= 10; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
   }
     
    switch (humiditydisplay){
     case -4 ... -1:
     case 0:
     case 1 ... 4:
     for (int i = 60; i <= 63; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 0

    case -9 ...-5:
    case 5 ... 9:
     for (int i = 65; i <= 67; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 5

    case -14 ...-10:
    case 10 ... 14:
     for (int i = 70; i <= 72; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 10

    case -19 ...-15:
    case 15 ... 19:
     for (int i = 75; i <= 77; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 15

    case -24 ...-20:
    case 20 ... 24:
     for (int i = 80; i <= 83; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 20

    case -29 ... -25:
    case 25 ... 29:
     for (int i = 52; i <= 54; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 25

    case -34 ... -30:
    case 30 ... 34:
     for (int i = 46; i <= 49; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 30

   case -39 ... -35:
   case 35 ... 39:
     for (int i = 42; i <= 45; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 35
       
   case -44 ... -40:
   case 40 ... 44:
     for (int i = 38; i <= 40; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 40

    case -100 ... -45:
    case 45 ... 100:
     for (int i = 30; i <= 35; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 45+ 
    
    default:
      for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(100,100,0); //yellow
      FastLED.show();
  }
      Serial.print("Sensor error");
      } //switch humiditydisplay
  
  //////////////////////////////////////////
 //  5. send all values to initial state //
//////////////////////////////////////////

  String url = "https://groker.init.st/api/events?accessKey=";
  url += accesskey;
  url += "&bucketKey=";
  url += bucketkey;
  url += "&temperature=";
  url += t;
  url += "&humidity=";
  url += h;
  url += "&heatIndex=";
  url += hic;
  url += "&outsideTemp=";
  url += Temperature;
  url += "&outsideHumidity=";
  url += Humidity;
  url += "&outsideHeatIndex=";
  url += HeatIndex;


//sent values to initial state via url
  Serial.print(F("requesting created URL: code "));
  https.begin(*client,url.c_str());

  https.setTimeout(5000);
  //Check for the returning code
  int serverhttpCode = https.GET();       
  
  Serial.print(serverhttpCode);
   
  if (serverhttpCode > 0) { 
      String payload = https.getString();
      Serial.println();
      Serial.println("values sent");
  } 
  else {
      Serial.print( https.errorToString(serverhttpCode).c_str() );
      Serial.println("Error on HTTP request");
      Serial.println("Debug or refresh");
      Serial.print(F("Restarting in 5 seconds..."));
      delay(5000);
      ESP.restart();    
  } //big else
  https.end(); //End 
} 
/*end of sending to initial state*/
     Serial.println("request URL ended");
     Serial.println("HTTP request ended");
     Serial.println("waiting 2 min");
// https.end(); 
 delay(120000);
  //delay for HTTPS request....
  }
}
