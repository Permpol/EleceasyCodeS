#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <SPI.h>
#include <TimeLib.h>
//#include <WidgetRTC.h>
#include <BlynkSimpleEsp32.h>
#include <SimpleTimer.h> //Blynk
#include <Timer.h>

char auth[] = "puzBx8DXSo2cqQA_1-pjjvopu1e7VNAX"; 
char server[] = "oasiskit.com";
int port = 8080;

char ssid[] = "Eleceasy"; // ชื่อไวไฟ ที่บอร์ดจะ connect
char pass[] = "Bb20072536"; // พาสเวิร์ดของไวไฟ

BlynkTimer timer;
WidgetRTC rtc;

// ฟังก์ชันนาฬิกาดิจิตอลแสดงเวลา
void clockDisplay()
{

  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + " " + month() + " " + year();
  Serial.print("Current time: ");
  Serial.print(currentTime);
  Serial.print(" ");
  Serial.print(currentDate);
  Serial.println();

  // ส่งเวลาไปที่แอพ
  Blynk.virtualWrite(V1, currentTime);
  // ส่งวันที่ไปที่แอพ
  Blynk.virtualWrite(V2, currentDate);
}

BLYNK_CONNECTED() {
  // ซิงโครไนซ์เวลาในการเชื่อมต่อ
  rtc.begin();
}

void setup()
{

  Serial.begin(115200);

  // แสดงนาฬิกาดิจิตอลทุก 10 วินาที
  timer.setInterval(10000L, clockDisplay);
  WiFi.begin(ssid, pass);
  Blynk.config(auth, server, port);
  Blynk.connect();
  setSyncInterval(10 * 60); // ช่วงเวลาการซิงค์เป็นวินาที (10 นาที)
}

void loop()
{
  Blynk.run();
  timer.run();
}