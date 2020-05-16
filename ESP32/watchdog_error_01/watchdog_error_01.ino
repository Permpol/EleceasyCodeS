#include <WiFi.h>
#include "time.h"
const byte core0 = 0;
const byte core1 = 1;
const byte pushButton =25;
const byte led =26;
const char* ssid       = "NYELOOGBALL";
const char* password   = "egat593618";
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600 * 7;
const int   daylightOffset_sec = 3600;
void coreTask0( void * pvParameters )
{
  pinMode(led, OUTPUT);
  for (;;)
  {
    digitalWrite(led, !digitalRead(led));
    Serial.println("CoreTask0 running on core " + String(xPortGetCoreID()));
    delay(1000);
  }
  vTaskDelete(NULL);
}
void coreTask1( void * pvParameters )
{
  pinMode(pushButton, INPUT);
  for (;;)
  {
    if (digitalRead(pushButton) == HIGH)
    {
      Serial.println("Push Button");
      Serial.println("CoreTask1 running on core " + String(xPortGetCoreID()));
      delay(1000);
    }
  }
  vTaskDelete(NULL);
}
void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}
void setup()
{
  Serial.begin(112500);
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  xTaskCreatePinnedToCore(coreTask0, "coreTask0", 10000, NULL, 1, NULL, core1);
  xTaskCreatePinnedToCore(coreTask1, "coreTask1", 10000, NULL, 1, NULL, core0);
}
void loop()
{
  printLocalTime();
  Serial.println("Loop running on core " + String(xPortGetCoreID()));
  delay(1000);
}