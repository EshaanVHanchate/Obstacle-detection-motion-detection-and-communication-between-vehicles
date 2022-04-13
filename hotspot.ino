#include <ESP8266WiFi.h>
WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);
#define pin 16
int IRsensor = 16;
#define pin 14
int myLed = 14;
#define pin 12
int otherLed = 12;
void setup() {
 Serial.begin(9600);
 pinMode(IRsensor,INPUT);
 pinMode(myLed,OUTPUT);
 pinMode(otherLed,OUTPUT);
 WiFi.mode(WIFI_AP);
 WiFi.softAP("Metamorphosis","symbiosis");
 WiFi.softAPConfig(IP, IP, mask);
 server.begin();
 Serial.println();
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
 client.flush();
 client.println(String(IrVal) + "\r");
 Serial.println("Sensor Value from client: " + request);
 Serial.print("My IR value: ");
 Serial.println(IrVal);
 if(IrVal == 1)
 {
  digitalWrite(myLed,LOW);
 }
 else if(IrVal == 0)
 {
  digitalWrite(myLed,HIGH);
 }
 if( request == "1")
 {
  digitalWrite(otherLed,LOW);
 }
 else if( request == "0")
 {
  digitalWrite(otherLed,HIGH);
 }
}
