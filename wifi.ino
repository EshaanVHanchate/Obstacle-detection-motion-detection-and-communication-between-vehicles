#include <ESP8266WiFi.h>
char ssid[] = "Metamorphosis";           // SSID of your AP
//char pass[] = "symbiosis";         // password of your AP
IPAddress server(192,168,4,15);     // IP address of the AP
#define pin 16
int IRsensor = 16;
#define pin 14
int myLed = 14;
#define pin 12
int otherLed = 12;
#define pin 5
int relay = 5;
WiFiClient client;
void setup() {
  Serial.begin(9600);
  pinMode(IRsensor,INPUT);
  pinMode(myLed,OUTPUT);
  pinMode(otherLed,OUTPUT);
  pinMode(relay,OUTPUT);
  WiFi.mode(WIFI_STA);
  //WiFi.begin(ssid,pass);  // connects to the WiFi AP
  WiFi.begin(ssid); 
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
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
  client.print(String(IrVal)+"\r");
  String answer = client.readStringUntil('\r');
  Serial.println(" Sensor value from the server: " + answer);
  if((IrVal == 0)||(answer == "0"))
 {
  digitalWrite(myLed,HIGH);
  digitalWrite(relay,LOW);
 }
 else
 {
  digitalWrite(myLed,LOW);
  digitalWrite(relay,HIGH);
 }
 if( answer == "1")
 {
  digitalWrite(otherLed,LOW);
 }
 else if( answer == "0")
 {
  digitalWrite(otherLed,HIGH);
 }
  client.flush();
  client.stop();
  delay(2000);
}
