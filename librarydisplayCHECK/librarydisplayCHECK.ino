#include <ArduinoJson.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

// LEDS
#include <FastLED.h>
#define NUM_LEDS 48     //Number of RGB LED beads
#define DATA_PIN D8    //The pin for controlling RGB LED
#define LED_TYPE WS2812B    //RGB LED strip type
CRGB leds[NUM_LEDS];    //Instantiate RGB LED

// DHT
#include "DHT.h"
#define DHTPIN D3    // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//-------------WiFi settings-----------------------------
const char* ssid = "CE-Hub-Student";
const char* password = "casa-ce-gagarin-public-service";

//-------------API user settings--------------------------
const char* clientId = "7338eda7ea694cad61cee72f9408af6f";
const char* clientSecret = "402e2616c73769757358630e92924062";
const char* APIurl = "https://api-metoffice.apiconnect.ibmcloud.com/v0/forecasts/point/hourly?excludeParameterMetadata=true&includeLocationName=true&latitude=51.5427233252536&longitude=0.004183041568396564";

//-----------Initial State user settings------------------
const char* accesskey = "ist_ianAvJO129YcntUonQFr0RXU289WelB8";
const char* bucketkey = "FE4J9P3CHYS6";

//----------const integers idfk tbh-----------------------
float Temperature;
float Humidity;
float HeatIndex;

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
   Serial.println("wake DHT up for 10 seconds");
   delay(10000);
  
 //init WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void loop () {
  /////////////////////////////////
 // 1. Make secured Get Request //
/////////////////////////////////

WiFiClientSecure *client = new WiFiClientSecure;
// set secure client without certificate
client->setInsecure();
//create an HTTPClient instance
HTTPClient https;

///AW suggestion: nest all of this in a more restrictive if statement (time wise)
//that do be making sense tho
https.begin(*client, APIurl);
Serial.print("[HTTPS] GET...\n");
https.addHeader("X-IBM-Client-Id", clientId);
https.addHeader("X-IBM-Client-Secret", clientSecret);
int httpCode = https.GET();
if (httpCode > 0) {
    String payload = https.getString();
    DynamicJsonDocument doc(49152);
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
//return;
    } else {
      float Temperature = doc["features"][0]["properties"]["timeSeries"][2]["screenTemperature"];
      float Humidity = doc["features"][0]["properties"]["timeSeries"][2]["screenRelativeHumidity"];
      float HeatIndex = doc["features"][0]["properties"]["timeSeries"][2]["feelsLikeTemperature"];
      Serial.print(F("Outside temperature: "));
      Serial.print(Temperature);
      Serial.print(F(" | Outside humidity: "));
      Serial.print(Humidity);
      Serial.print(F(" | Ambient temperature: "));
      Serial.println(HeatIndex);
      // TODO: Handle LED control based on the API values
    }
  } else {
    Serial.println(F("Error on API request"));
  }

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
    Serial.println(F("Giving myself 2 minutes to debug..."));
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

/*uhhh its gonna be Temperature - t ... kinda weird*/

    int displayTemp = t - Temperature;
      Serial.print(F("displayTemp = "));
      Serial.print(displayTemp);
      Serial.print(F("°C"));
      Serial.println();
    //DHT temperature - met office screen air temperature
    //later can change to calculated heat index - met office feels like temperature

   int displayHumidity = h - Humidity;
   Serial.print(F("displayHumidity = "));
   Serial.print(displayHumidity);
   Serial.print(F("%"));
   Serial.println();

   int indexDifference = hic - HeatIndex;
   Serial.print(F("Ambient temperature difference = "));
   Serial.print(indexDifference);
   Serial.print(F("°C"));
   Serial.println();
   
//oh that's fr all i need ok

  ////////////////////////////////////////////
 //  4. Light up corresponding LED lights  //
////////////////////////////////////////////

//a thousand if and or statements
  

 if ((displayTemp > 10) && (displayTemp <= 16)) {
  leds[8] = CRGB (200, 200, 200);
  leds[9] = CRGB (200, 200, 200);
  FastLED.show();
  Serial.println(F("lights up"));
  }
  else{
    for (int i = 8; i <= 9; i++){
    leds[i] = CRGB(random(0,255),random(0,255),random(0,255));
    FastLED.show();
    }   
  //leds[8] = CRGB (200, 100, 200);
  //leds[9] = CRGB (200, 100, 200);
  //FastLED.show();
    Serial.println("ok nice");
    }


  /////////////////////////////////////////
 //  5. send all values to web server   //
/////////////////////////////////////////

/* initial state stuff*/
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
  // ask.begin;
  https.begin(url); //Specify the URL
  
  //Check for the returning code
  int dashboardhttpCode = https.GET();       
  
  Serial.print(dashboardhttpCode);
   
  if (dashboardhttpCode > 0) { 
      String payload = https.getString();
      Serial.println();
      Serial.println("values sent");
  } else {
      Serial.println("Error on HTTP request");
      Serial.println("Debug or refresh");
      leds[16] = CRGB (200, 150, 150);
      leds[17] = CRGB (200, 150, 150);
      leds[18] = CRGB (200, 150, 150);  
      FastLED.show();
  }
 // UNCOMMENT IF ERROR https.end(); //End 

/*end of sending to initial state*/
     Serial.println("request URL ended");
     Serial.println("HTTP request ended");
     Serial.println("waiting 2 min");
 https.end(); 
 delay(120000);
  //delay for HTTPS request.... eerm hopefully it will not break PLSSSS it didnt yay
}
