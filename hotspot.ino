#include <ESP8266WiFi.h>
WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);
#define pin 16
int IRsensor = 16;
#define pin 14
int led = 14;
void setup() {
 Serial.begin(9600);
 pinMode(IRsensor,INPUT);
 pinMode(led,OUTPUT);
 WiFi.mode(WIFI_AP);
 WiFi.softAP("Wemos_AP", "Wemos_comm");
 WiFi.softAPConfig(IP, IP, mask);
 server.begin();
 Serial.println();
 Serial.println("accesspoint_bare_01.ino");
 Serial.println("Server started.");
 Serial.print("IP: "); Serial.println(WiFi.softAPIP());
 Serial.print("MAC:"); Serial.println(WiFi.softAPmacAddress());
}
void loop() {
 WiFiClient client = server.available();
 if (!client) {return;}
 String request = client.readStringUntil('\r');
 int IrVal = digitalRead(IRsensor);
 Serial.println("********************************");
 Serial.println("From the station: " + request);
 client.flush();
 Serial.print("Byte sent to the station: ");
 Serial.println(client.println(String(IrVal) + "\r"));
 Serial.print("Sensor Value from other: ");
 Serial.println(request);
 Serial.print("My IR value: ");
 Serial.println(IrVal);
}
