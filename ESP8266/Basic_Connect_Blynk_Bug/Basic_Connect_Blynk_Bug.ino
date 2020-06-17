#define BLYNK_PRINT Serial 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = ".....q8R"; //Token key LightBiO
//char auth[] = ".....Rxf"; //Token key LightPor
char server[] = "oasiskit.com";
char ssid[] = "Office";
char pass[] = "1212312121hay";
int port = 8080;

void setup() {
  Serial.begin(9600);
  Serial.println("กำลังเชื่อมต่อไปที่ Blynk Server");
  WiFi.begin(ssid, pass); //เชื่อมต่อ WiFi
  Blynk.config(auth, server, port); //กำหนด Token key , ชื่อ Server และ port
  Blynk.connect(); //เชื่อมต่อไปยัง Blynk
}

BLYNK_CONNECTED() {  // ฟังก์ชันนี้ทำงานเมื่อต่อ Blynk ได้ 
  Serial.println("App Blynk ทำงาน!");
}

void loop() {
  
  Blynk.run();
  delay(200);
}
