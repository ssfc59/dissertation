#include <FastLED.h>
#define NUM_LEDS 192     //Number of RGB LED beads
#define DATA_PIN D8    //The pin for controlling RGB LED
#define LED_TYPE WS2812B    //RGB LED strip type
CRGB leds[NUM_LEDS];    //Instantiate RGB LED

const int libHumidity = 0;
const int areaHumidity = 20;
const int libTemp = 20;
const int areaTemp = 20;

void setup() { 
  Serial.begin(115200);
   FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);     //Initialize RGB LED
}

void loop() {
  int display = libHumidity - areaHumidity;
  int tempdisplay = libTemp - areaTemp;

  Serial.println(display);

  if (tempdisplay <= 0) {
    //COOLER INSIDE THE LIBRARY
       for (int i = 92; i <= 102; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    }
    else if (tempdisplay > 0) {
       for (int i = 109; i <= 122; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
      }
switch (tempdisplay){
    case -5:
    case 5:
     for (int i = 128; i <= 130; i++) {
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
    break; //end case light up 8

   case -4:
   case 4:
     for (int i = 169; i <= 170; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 4

    case -3:
   case 3:
     for (int i = 174; i <= 176; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 3
    
   case -2:
   case 2:
     for (int i = 179; i <= 181; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 2

   case -1:
   case 1:
     for (int i = 184; i <= 186; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 1

   case 0:
     for (int i = 189; i <= 191; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 1

   default:
      for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(100,100,0); //yellow
      FastLED.show();
  }
      Serial.print("Sensor error");
  }
  
 if (display <= 0) {
  //LESS HUMID
   for (int i = 13; i <= 19; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
 }
   else if (display > 0){
    //MORE HUMID
     for (int i = 13; i <= 19; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
   }
     
    switch (display){
    case -100 ... -45:
    case 45 ... -100:
     for (int i = 32; i <= 35; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 45 

   case -44 ... -40:
   case 40 ... 44:
     for (int i = 38; i <= 41; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 40

    
   case -39 ... -35:
   case 35 ... 39:
     for (int i = 42; i <= 45; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 35
    
    case -34 ... -30:
    case 30 ... 34:
     for (int i = 46; i <= 50; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 30

    case -29 ... -25:
    case 25 ... 29:
     for (int i = 51; i <= 54; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 25

     case -4 ... -1:
     case 0:
     case 1 ... 4:
     for (int i = 60; i <= 63 ; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();
    }
    break; //end case light up 0

    case -9 ...-5:
    case 5 ... 9:
     for (int i = 66; i <= 69; i++) {
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
     for (int i = 75; i <= 78; i++) {
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
       
    default:
      for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(100,100,0); //yellow
      FastLED.show();
  }
      Serial.print("Sensor error");
      } //switch display

 delay(5000);
}

  //leds[0] = CRGB(random(0,255),random(0,255),random(0,255));    // LED shows a randomly mixed color
