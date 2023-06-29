#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ArduinoHttpClient.h>

const char *ssid = "CE-Hub-Student";  //ENTER YOUR WIFI SETTINGS
const char *password = "casa-ce-gagarin-public-service";

const char* host = "api-metoffice.apiconnect.ibmcloud.com";
const int httpsPort = 443;
const char* endpoint = "/v0/forecasts/point/hourly?excludeParameterMetadata=false&includeLocationName=true&latitude=51.5427233252536&longitude=0.004183041568396564";
const char* clientId = "7338eda7ea694cad61cee72f9408af6f";
const char* clientSecret = "402e2616c73769757358630e92924062";

const char fingerprint[] PROGMEM = "BC 7B CA 4F 27 E7 31 A2 FB 0A D9 DB DC 56 FA 13 BE AA 1B 9D";

//API variables
int time;
int temperature;

//JSON document
DynamicJsonDocument doc(2048);

WiFiClient client;
HttpClient http;

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (!client.connected()) {
      //client.setInsecure();
      client.connect(host, httpsPort);
    }

    if (client.connected()) {
      String url = "https://" + String(host) + String(endpoint);
      http.begin(client, url);
      http.addHeader("X-IBM-Client-Id", clientId);
      http.addHeader("X-IBM-Client-Secret", clientSecret);

      int httpResponseCode = http.GET();
      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);

        // Parse the JSON response
        StaticJsonDocument<1024> jsonDocument;
        DeserializationError error = deserializeJson(jsonDocument, response);

        if (error) {
          Serial.print("Error parsing JSON: ");
          Serial.println(error.c_str());
        } else {
          // Access specific keys and values
          JsonArray forecasts = jsonDocument["features"]["properties"]["timeSeries"];
          for (JsonVariant forecast : forecasts) {
            // Access specific columns and rows
            String time = forecast["time"].as<String>();
            double temperature = forecast["screenTemperature"]["value"].as<double>();

            // Print the desired values to the serial monitor
            Serial.print("Time: ");
            Serial.println(time);
            Serial.print("Temperature: ");
            Serial.println(temperature);
            Serial.println("----------------------------------");
          }
        }
      } else {
        Serial.print("Error on HTTP request: ");
        Serial.println(httpResponseCode);
      }

      http.end();
      client.stop();
    }
  }

  delay(5000); // Wait for 5 seconds before making the next request
}
