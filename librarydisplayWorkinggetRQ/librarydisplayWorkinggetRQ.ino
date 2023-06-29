
/*
  Complete project details: https://RandomNerdTutorials.com/esp32-https-requests/
  Based on the BasicHTTPSClient.ino example found at Examples > BasicHttpsClient
*/
#include <ArduinoJson.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

#include <FastLED.h>
#define NUM_LEDS 48     //Number of RGB LED beads
#define DATA_PIN D8    //The pin for controlling RGB LED
#define LED_TYPE WS2812B    //RGB LED strip type
CRGB leds[NUM_LEDS];  

// Replace with your network credentials
const char* ssid = "CE-Hub-Student";
const char* password = "casa-ce-gagarin-public-service";
const char* clientId = "7338eda7ea694cad61cee72f9408af6f";
const char* clientSecret = "402e2616c73769757358630e92924062";

void setup() {
  Serial.begin(115200);
  Serial.println();
  // Initialize Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void loop() {
 WiFiClientSecure *client = new WiFiClientSecure;
  if(client) {
    // set secure client without certificate
    client->setInsecure();
    //create an HTTPClient instance
    HTTPClient https;

    //Initializing an HTTPS communication using the secure client
    Serial.print("[HTTPS] begin...\n");
   https.useHTTP10(true);
   
  if(https.begin(*client,"https://api-metoffice.apiconnect.ibmcloud.com/v0/forecasts/point/hourly?excludeParameterMetadata=true&includeLocationName=true&latitude=51.5427233252536&longitude=0.004183041568396564"))
    {  // HTTPS
      Serial.print("[HTTPS] GET...\n");
      https.addHeader("X-IBM-Client-Id", clientId);
      https.addHeader("X-IBM-Client-Secret", clientSecret);
      // start connection and send HTTP header
      int httpCode = https.GET();
      // httpCode will be negative on error
      if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
       Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          https.GET();

// Parse response
DynamicJsonDocument doc(49152);
deserializeJson(doc, https.getStream());
          // print server response payload
         // String payload = https.getString();
        //  Serial.println(payload);
const char* type = doc["type"];
Serial.println(type);
      

//DynamicJsonDocument doc(49152);

DeserializationError error = deserializeJson(doc, https.getStream());

if (error) {
  Serial.print("deserializeJson() failed: ");
  Serial.println(error.c_str());
  return;
}


        }
      }
      else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    }
  }
  else {
    Serial.printf("[HTTPS] Unable to connect\n");
  }
  Serial.println();
  Serial.println("Waiting 2min before the next round...");
  delay(120000);
}
