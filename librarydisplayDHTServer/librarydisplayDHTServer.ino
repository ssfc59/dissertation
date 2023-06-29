#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN D2    // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#include <FastLED.h>
#define NUM_LEDS 48     //Number of RGB LED beads
#define DATA_PIN D8    //The pin for controlling RGB LED
#define LED_TYPE WS2812B    //RGB LED strip type
CRGB leds[NUM_LEDS];   



//-------- User Settings -----------
const char* ssid = "CE-Hub-Student";
const char* password = "casa-ce-gagarin-public-service";
const char* accesskey = "ist_ianAvJO129YcntUonQFr0RXU289WelB8";
const char* bucketkey = "FE4J9P3CHYS6";
//----------------------------------

HTTPClient ask;
int counter = 0;  
static bool hasWifi = false;

//////////////
// Network //
////////////

static void InitWifi()
{
  Serial.println("Connecting...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  hasWifi = true;
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup()
{
  Serial.begin(115200);
  Serial.println("ESP32 Device");
  Serial.println("Initializing...");
  
  dht.begin();

  // Initialize the WiFi module
  Serial.println(" > WiFi");
  hasWifi = false;
  InitWifi();
  if (!hasWifi)
  {
    return;
  }
  Serial.println("wake the DHT sensor up for 10 seconds...");
  delay(10000); 
   Serial.println("lets hope its awake..."); 
}

//////////////
//Send Data//
////////////

void loop(){
  if (WiFi.status() == WL_CONNECTED) { //if we are connected
    counter = 0; //reset counter
    Serial.println("Wifi is still connected with IP: "); 
    Serial.println(WiFi.localIP());   //inform user about his IP address
  }else if (WiFi.status() != WL_CONNECTED) { //if we lost connection, retry
    WiFi.begin(ssid);      
  }
  while (WiFi.status() != WL_CONNECTED) { //during lost connection, print dots
    delay(500);
    Serial.print(".");
    counter++;
    if(counter>=60){ //30 seconds timeout - reset board
    ESP.restart();
    }
  }

  // Reading temperature, humidity and heat index
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float hic = dht.computeHeatIndex(t, h, false);
  //heat index = what the temperature feels like to the human body when relative humidity is combined with the air temperature.
  //false so it returns values in degrees Celsius

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)|| isnan(hic)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F("°C |"));
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("% |"));
  Serial.print(F("Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  
  // Create a URL for the request
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

  Serial.println("requesting created URL: code ");
  // ask.begin;
  ask.begin(url); //Specify the URL
  
  //Check for the returning code
  int httpCode = ask.GET();       
  
  Serial.print(httpCode);
   
  if (httpCode > 0) { 
      String payload = ask.getString();
      Serial.println("values sent");
  } else {
      Serial.println("Error on HTTP request");
  }
  ask.end(); //End 
  Serial.println("***End***");
  Serial.println("waiting 30 secs before sending the next values...");
  delay(30000);    // delay
}
