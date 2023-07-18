#include <FastLED.h>
#define NUM_LEDS 192     //Number of RGB LED beads
#define DATA_PIN D8    //The pin for controlling RGB LED
#define LED_TYPE WS2812B    //RGB LED strip type
CRGB leds[NUM_LEDS];    //Instantiate RGB LED

const int libHumidity = 0;
const int areaHumidity = 20;

void setup() { 
  Serial.begin(115200);
   FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);     //Initialize RGB LED
}

void loop() {
  int display = libHumidity - areaHumidity;
  
  //display = -16!
  Serial.println(display);

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
      // for (int i = 31; i <= 35; i++)
      //80 83 is 20
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
 
  
}

// for(int i = 0; i < NUM_LEDS; i++)
/*
   for (int i = 7; i <= 9; i++) {
    leds[i] = CRGB (100, 100, 100);
    FastLED.show();
    }
  
   for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(255,255,255);
      FastLED.show();
      }

    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i]= CRGB (255, 255, 255);
  }
 
  */

  //leds[0] = CRGB(random(0,255),random(0,255),random(0,255));    // LED shows a randomly mixed color
