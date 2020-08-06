#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"


char auth[] = "9d2ea3c204d3494caa739e5ab32a397f";
char ssid[] = "Anuwat";
char pass[] = "0817876668";

#define DHTPIN 15
#define DHTTYPE DHT22     // DHT 22

DHT dht(DHTPIN, DHTTYPE);

const int Relay1  = 13;
const int Relay2  = 12;
const int Relay3  = 14;
const int Relay4  = 27;
bool buttonStatus = 0;

WidgetLED ledBlynk(V10);

BlynkTimer timer;

BLYNK_CONNECTED() {
  Blynk.syncAll();
}


 BLYNK_WRITE(V1)
{

 if(param.asInt() == 0)
  {
    digitalWrite(Relay1, HIGH);
    Serial.println("LED Turned ON");
    Blynk.virtualWrite(V13, 1);
    ledBlynk.on();
  }
  else
  {
    digitalWrite(Relay1, LOW);
    Serial.println("LED Turned OFF");
    Blynk.virtualWrite(V13, 0);
    ledBlynk.off(); 

  }
 }
BLYNK_WRITE(V13)
{
  if (param.asInt() == 0)
  {
    digitalWrite(Relay1, LOW);
    ledBlynk.off();
  }
  if (param.asInt() == 1)
  {
    digitalWrite(Relay1, HIGH);
    ledBlynk.on();
  }
}
 BLYNK_WRITE(V2) 
  {
 if(param.asInt() == 0)
  {
    digitalWrite(Relay2, HIGH);
    Serial.println("LED Turned ON");
    Blynk.virtualWrite(V12, 1);
    ledBlynk.on();
  }
  else
  {
    digitalWrite(Relay2, LOW);
    Serial.println("LED Turned OFF");
    Blynk.virtualWrite(V12, 0);
    ledBlynk.off(); 

  }
 }
BLYNK_WRITE(V12)
{
  if (param.asInt() == 0)
  {
    digitalWrite(Relay2, LOW);
    ledBlynk.off();
  }
  if (param.asInt() == 1)
  {
    digitalWrite(Relay2, HIGH);
    ledBlynk.on();
  }
}
 BLYNK_WRITE(V3) 
  {
 if(param.asInt() == 0)
  {
    digitalWrite(Relay3, HIGH);
    Serial.println("LED Turned ON");
    Blynk.virtualWrite(V14, 1);
    ledBlynk.on();
  }
  else
  {
    digitalWrite(Relay3, LOW);
    Serial.println("LED Turned OFF");
    Blynk.virtualWrite(V14, 0);
    ledBlynk.off(); 

  }
 }
BLYNK_WRITE(V14)
{
  if (param.asInt() == 0)
  {
    digitalWrite(Relay3, LOW);
    ledBlynk.off();
  }
  if (param.asInt() == 1)
  {
    digitalWrite(Relay3, HIGH);
    ledBlynk.on();
  }
}
BLYNK_WRITE(V4) 
  {
 if(param.asInt() == 0)
  {
    digitalWrite(Relay4, HIGH);
    Serial.println("LED Turned ON");
    Blynk.virtualWrite(V27, 1);
    ledBlynk.on();
  }
  else
  {
    digitalWrite(Relay4, LOW);
    Serial.println("LED Turned OFF");
    Blynk.virtualWrite(V27, 0);
    ledBlynk.off(); 

  }
 }
BLYNK_WRITE(V27)
{
  if (param.asInt() == 0)
  {
    digitalWrite(Relay4, LOW);
    ledBlynk.off();
  }
  if (param.asInt() == 1)
  {
    digitalWrite(Relay4, HIGH);
    ledBlynk.on();
  }
}
void setup() 
{
 Serial.begin(9600);
Serial.println();
Serial.println("DHTxx test!");
 
  dht.begin();
 //Relay
 pinMode(Relay1, OUTPUT);
 pinMode(Relay2, OUTPUT);
 pinMode(Relay3, OUTPUT);
 pinMode(Relay4, OUTPUT);
 //set default status
 digitalWrite(Relay1, LOW);
 digitalWrite(Relay2, LOW);
 digitalWrite(Relay3, LOW);
 digitalWrite(Relay4, LOW);

 Blynk.begin(auth, ssid, pass);

}
void loop()
{   
 Blynk.run(); 
 timer.run();
}