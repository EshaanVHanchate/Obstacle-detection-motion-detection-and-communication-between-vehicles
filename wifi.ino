#include <ESP8266WiFi.h>
char ssid[] = "Wemos_AP";           // SSID of your AP
char pass[] = "Wemos_comm";         // password of your AP
IPAddress server(192,168,4,15);     // IP address of the AP
#define pin 16
int IRsensor = 16;
#define pin 14
int led = 14;
WiFiClient client;
void setup() {
  Serial.begin(9600);
  pinMode(IRsensor,INPUT);
  pinMode(led,OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.println("station_bare_01.ino");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());

}
void loop() {
  client.connect(server, 80);
  int IrVal = digitalRead(IRsensor);
  
  Serial.println("********************************");
  Serial.print("My IR val: ");
  Serial.println(IrVal);
  Serial.print("Byte sent to the AP: ");
  Serial.println(client.print(String(IrVal)+"\r"));
  String answer = client.readStringUntil('\r');
  Serial.println(" Sensor value from the AP: " + answer);
  client.flush();
  client.stop();
  delay(2000);
}
