# Warm Reminders in Cool Spaces: Real-time monitoring of the thermal environment in Stratford Library with an integrated sensing and display device

## Overview

![image](https://github.com/ssfc59/dissertation/assets/114293506/42fe1c9b-c6e6-480d-82f4-f696fb539e88)
![image](https://github.com/ssfc59/dissertation/assets/114293506/bbdb646f-a900-4213-85d3-9c15a9342178)
![image](https://github.com/ssfc59/dissertation/assets/114293506/eda450a7-a2c0-4460-a067-1a921de291c1)


This "Warm Reminder" is a device that both senses and shows the real-time comparative temperature and humidity inside Stratford Library, a designated Tier 1 Cool Space by the Greater London Authority, and the surrounding area. It also sends the exact values recorded by the device over time to a data visualisation platform.

 As part of a collaboration with Newham Council and Stratford Library staff, this device was deployed in the library to inform both library staff and visitors of the facility's cooling efficacy and investigate its adherence to the 2023 Cool space criteria of having a "cooler indoor temperature than outdoors" during hot weather.

It aimed to engage both the public and the government on the emerging problem of heat, which could enourage heat adapation measures on both an individual and urban management level to increase community climate resilience to the adverse effects of extreme heat exposure.

To see the exact values recorded by this device, [click here](https://go.init.st/6woxrdn) or scan the QR code, and [click here to view the GLA Cool Spaces Map.](https://apps.london.gov.uk/cool-spaces/)

## Research Question
Can deploying a real-time integrated temperature and humidity sensing and display device inside Stratford Library help to indicate its cooling efficacy as a cool space over time?

## Device Function
The device takes the form of a large book-shaped light-up textual display that shows a comparative sentence of Stratford Library’s temperature and humidity values compared to outside on its “book cover”. 

It is run by a **FireBeetle ESP32 IOT Microcontroller**, which controls a **WS2812B LED strip** on the inside and a **DHT22 temperature and humidity sensor** on its side. 

Every 3 minutes from 9am-8pm, Stratford Library’s opening hours, the device collects and compares temperature, humidity, and heat index readings from the DHT22 sensor and the Met Office’s Weather DataHub, lights up the corresponding values and modifiers on the display, then sends the collected values to Initial State, a data visualisation platform that visualises the exact values of each variable over time on multiple charts.

## Device Fabrication
My device incorporates the visual features of a book, including its shape, material, proportion, and textual display format in its design as a reference to its placement in Stratford Library.

I used boxes.py, Fusion360, and Adobe Illustrator to make a laser cut template of a book shaped box with a curved side, with cut out stencilled text of the value displays onto its front, and cut it out of black acrylic. 

![image](https://github.com/ssfc59/dissertation/assets/114293506/a07bb29a-c4c4-4717-a4d6-c9e9030a4df6)
![image](https://github.com/ssfc59/dissertation/assets/114293506/759ab18f-8b37-40d8-bef8-4715ece600e1)

I then attached the LED strip to the back of each display row.

![image](https://github.com/ssfc59/dissertation/assets/114293506/d77ad8de-451d-4161-9713-f613c7ae1a68)

Lastly, I designed and laser cut a paper overlay with permanent parts of the sentence display and placed it on the device's front face to conceal the cutouts, only allowing the LED-lit values and descriptors to be visible.

![image](https://github.com/ssfc59/dissertation/assets/114293506/aabf1907-3425-4a99-b8bc-e1fee5e3c0c8)
![image](https://github.com/ssfc59/dissertation/assets/114293506/4d6bf1b3-457a-41f8-857c-0e4c8e75eed2)

I also laser cut 2 vertically lined pieces of white paper and placed them on the sides, making it resemble the pages of a book between book covers.

![image](https://github.com/ssfc59/dissertation/assets/114293506/08d5a813-1c18-4a40-b3a9-f44d16c82002)

When the device is working, the display shows a sentence that compares the real-time temperature and humidity values inside Stratford Library to that outside. 

![image](https://github.com/ssfc59/dissertation/assets/114293506/7572d617-b346-4f9d-b744-59d562b0a4cc)


## Code Components
After connecting to WiFi successfully, my device’s code comprises 6 main chunks:

1.	Obtain the current hour and run the rest of the code if it is between 9am-8pm.

2.	Make a secured Get request to the Weather DataHub API to obtain the temperature, humidity, and “feels like” temperature of the area around Stratford Library.

3.	Obtain temperature, humidity, and heat index readings from the DHT22 sensor.

4.	Subtract the API values from the sensor values to find the temperature and humidity difference between Stratford Library and the surrounding outdoor area.

5.	Light up the LED lights to illuminate the corresponding numerical values and text descriptions on the display.

6.	Post all the received values to Initial State.

7.	2-minute delay between iterations.


### Arduino Libraries:

- [EzTime Library](https://github.com/ropg/ezTime) was used to obtain the current hour in a simple way.
- [ArduinoJson](https://arduinojson.org/) was used to deserialise the API response from Met Office DataHub.
- [WiFiClientSecure](https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFiClientSecure/README.md) was used to make secure GET and POST requests.
- [FastLED](https://github.com/FastLED/FastLED) was used to control the LED lights.

## Repository contents
- Code
- Laser cut templates
- 3D printed ESP32 enclosure
- Data collected
