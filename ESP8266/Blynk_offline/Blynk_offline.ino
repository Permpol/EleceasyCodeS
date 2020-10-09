#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleDHT.h>
#include <SimpleTimer.h>
//ปั้ม
 int pinPump1 = D2;
 int pinPump2 = D3;
 int pinPump3 = D4;
// DHT Config
int pinDHT22 = D0;
SimpleDHT22 dht22;

// SET Timer
SimpleTimer timer;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "0z0F7zDnJ4fReHWSGlrFo8Zc3wz9S7r8";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Eleceasy";
char pass[] = "XXXXXXXXX";
// Line config

BLYNK_CONNECTED() {
    Blynk.syncAll();
}


  float temperature = 0;
  float humidity = 0;

int setTemp;
int setHumid;

BLYNK_WRITE(V4) //temperature slider in app on pin V4
{
setTemp = param.asFloat();
}
BLYNK_WRITE(V3) //temperature slider in app on pin V3
{
setHumid = param.asFloat();
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  // You can also specify server:
  Blynk.begin(auth, ssid, pass, "oasiskit.com", 8080);
  timer.setInterval(4000L, sendTemp);
  pinMode(pinPump1, OUTPUT);
  pinMode(pinPump2, OUTPUT);
  pinMode(pinPump3, OUTPUT);
}

void sendTemp()
{
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(pinDHT22, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); Serial.println(err);delay(4000);
    return;
}  
  Blynk.virtualWrite(V1, temperature); // virtual pin 
  Blynk.virtualWrite(V2, humidity); // virtual pin 
}

void loop()
{

  Blynk.run();
  if (temperature >= setTemp)
  {
    digitalWrite(pinPump1, HIGH);
    digitalWrite(pinPump2, HIGH);
    digitalWrite(pinPump3, HIGH);
  }
  else
  {
    digitalWrite(pinPump1, LOW);
    digitalWrite(pinPump2, LOW);
    digitalWrite(pinPump3, LOW);
  }
  if (humidity <= setHumid)
  {
    digitalWrite(pinPump1, HIGH);
    digitalWrite(pinPump2, HIGH);
    digitalWrite(pinPump3, HIGH);
  }
  else
  {
    digitalWrite(pinPump1, LOW);
    digitalWrite(pinPump2, LOW);
    digitalWrite(pinPump3, LOW);
  }
}
