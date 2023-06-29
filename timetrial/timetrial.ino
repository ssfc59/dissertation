#include <WiFi.h>
#include <ezTime.h>

Timezone myTimezone;
const char* ssid     = "CE-Hub-Student";
const char* password = "casa-ce-gagarin-public-service";
int startHour = 8;    // Start hour (24-hour format)
int endHour = 20;

void setup() {
  // Other setup code...
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

    waitForSync();
myTimezone.setPosix("GMT0BST,M3.5.0/1,M10.5.0");
}

void loop() {
  // Other code...

  int currentHour = myTimezone.hour();
 Serial.println(currentHour);
 
  if (currentHour >= startHour && currentHour < endHour) {
    Serial.println("I WANT TO GO HOME NOW");
  }
  else
  {
    Serial.println("aight nvm");
    }
     delay(3000);
}
