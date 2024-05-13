#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266HTTPClient.h>
#include <Servo.h>
#include <RtcDS1302.h>
#include <ThreeWire.h>
#include <WiFiClient.h>


const char auth[] = ""; // your blynk auth token
const char ssid[] = ""; // your wifi ssid
const char pass[] = ""; // your wifi password

#define TRIG_PIN D1
#define ECHO_PIN D7

#define RED_LED D0
#define GREEN_LED D2

long distance;
bool open = false;
String start;

Servo servo;
WiFiClient wclient;
ThreeWire rtcWire(D4, D3, D5);  // DAT CLK RST
RtcDS1302<ThreeWire> Rtc(rtcWire);

void setup() {
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) { // Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  } 

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  Rtc.Begin();
  Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));

  servo.attach(D6);
  servo.write(0);
  delay(1500); // For some other stuff to get ready
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime();
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  distance = pulseIn(ECHO_PIN, HIGH) * 0.034 / 2;

  if (distance <= 40) {
    servo.write(90);
    if (!open) {
      start = getDateTime(now);
      open = true;
    }
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    Blynk.virtualWrite(V0, "open");
  } else {
    servo.write(0);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    Blynk.virtualWrite(V0, "closed");
    if (open) {
      sendTimeStamp(start, getDateTime(now));
    }
    open = false;
  }
}

String getDateTime(const RtcDateTime& dt) {
  char datestring[20];
  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Month(), dt.Day(), dt.Year(),
             dt.Hour(), dt.Minute(), dt.Second());
  return datestring;
}

void sendTimeStamp(String start, String end) {
  HTTPClient http;
  http.begin(wclient, "http://your_host_ip:your_port/api/timestamp"); // put your host and port
  http.addHeader("Content-Type", "application/json");

  String post_data = "{\"gateOpen\": \"" + start + "\", \"gateClosed\": \"" + end + "\", \"access_key\": \"87bf*@)pSDF\"}";

  int responseCode = http.POST(post_data);
  Serial.println(responseCode);
  Serial.println(http.getString());

  http.end();
}