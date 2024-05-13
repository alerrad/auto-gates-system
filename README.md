# Automatic gates system

Just a fun little IoT project. Automatic gates with the logbook for opening timestamps. Every record is stored in a cloud mongoDB Atlas.

## Schematic & parts
parts used:
- breadboard *(x1)*
- ESP8266 *(x1)*
- Micro Servo 9g *(x1)*
- RTC module - 2 *(x1)*
- HC-SR04 *(x1)*
- LEDs *(1 green and 1 red)*
- Jumper wires

## Logic
Once the ultrasonic sensor detecs an object (e.g. a car) it triggers servo motor to turn 90 degrees (kind of gates opening) and then the RTC module loggs the datetime which is then sent to REST API endpoint to further save it in a MongoDB cluster and sets "open" status in the blynk dashboard. Once the object is gone "closed" status is set in blynk console.

## Running the REST nodejs API
To run the REST API locally you can build the dockerfile and run the container or simply run it via nodejs. Don't forget to set your own ENV variables as in [.env.example](./server/.env.example). Make sure that your ESP8266 is connected to the same WiFi as your machine running the REST API.

## License
This repo is licensed under [MIT license](./LICENSE).