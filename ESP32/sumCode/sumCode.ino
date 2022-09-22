#include <WiFi.h>
#include "time.h"
#include <TridentTD_LineNotify.h>
#define SSID        "******"
#define PASSWORD    "******"
#define LINE_TOKEN  "*************"
#define LED 2

const char* ntpServer = "pool.ntp.org"; 
const long  gmtOffset_sec = 0 * 3600;
const int   daylightOffset_sec = 7 * 3600;

bool Normal = false;
bool High = false;
bool Low = false;
bool Off = false;
unsigned long period =  3600000 * 12ul ;
unsigned long last_time = 0;
PZEM004Tv30 pzem(Serial1, 16, 17);

void printLocalTime()

{
   struct tm timeinfo;
   if (!getLocalTime(&timeinfo)) {
     Serial.println("Failed to obtain time");
     return;
   }
   Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
 }


void setup() {  

  pinMode(LED, OUTPUT);
  Serial.begin(115200); 
  Serial.println();
  Serial.println(LINE.getVersion());

  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
   }
            
  Serial.println(" CONNECTED");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime(); 
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
  LINE.setToken(LINE_TOKEN);
  LINE.notify("Node..WatKhaoDinNongSaeng-Site");
  delay(500);

  Serial.begin(115200);

  // delete old config
  WiFi.disconnect(true);

  delay(1000);

  WiFi.onEvent(WiFiStationConnected, SYSTEM_EVENT_STA_CONNECTED);
  WiFi.onEvent(WiFiGotIP, SYSTEM_EVENT_STA_GOT_IP);
  WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);

  /* Remove WiFi event
  Serial.print("WiFi Event ID: ");
  Serial.println(eventID);
  WiFi.removeEvent(eventID);*/

  WiFi.begin(ssid, password);
    
  Serial.println();
  Serial.println();
  Serial.println("Wait for WiFi... ");
  
}

void loop() {

  delay(500);
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);

  if ( millis() - last_time > period) {
    Normal = false;
    Low = false;
    High = false;
    Off = false;
    last_time = millis();

   }

  float voltage = pzem.voltage();
  Serial.println("Read:" + String(voltage));
  if (voltage >= 381) {
    Serial.println("Voltage read Error");
    delay(2000);
    return;
  }

  else if (voltage >= 171 && voltage <= 250) {
    if (Normal == false) {
      Normal = true;
      Low = false;
      High = false;
      Off = false;
      last_time = millis();

      LINE.notify("WatKhaoDinNongSaeng Voltage : " + String(voltage) + " Normal");
      Serial.println("Line :WatKhaoDinNongSaeng Voltage : " + String(voltage) + " Normal");
    }
  }
  else if (voltage >= 1 && voltage <= 170) {
    if (Low == false) {
      Low = true;
      Normal = false;
      LINE.notify("WatKhaoDinNongSaeng Voltage : " + String(voltage) + " Low");
      Serial.println("Line :WatKhaoDinNongSaeng Voltage : " + String(voltage) + " Low");
    }
  }
  else if (voltage >= 251 && voltage <= 380) {
    if (High == false) {
      High = true;
      Normal = false;
      LINE.notify("WatKhaoDinNongSaeng  Voltage : " + String(voltage) + " High");
      Serial.println("Lins :WatKhaoDinNongSaeng  Voltage :" + String(voltage) + " High");
    }
  }
  else if (isnan(voltage)) {
    if (Off == false) {
      Off = true;
      Normal = false;
      LINE.notify("WatKhaoDinNongSaeng Voltage : " + String(voltage) + " Off");
      Serial.println("Lins :WatKhaoDinNongSaeng Voltage : " + String(voltage) + " Off");
    }
  }

  Serial.println();
  delay(1500);
}

void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info){
  Serial.println("Connected to AP successfully!");
}

void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info){
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info){
  Serial.println("Disconnected from WiFi access point");
  Serial.print("WiFi lost connection. Reason: ");
  Serial.println(info.disconnected.reason);
  Serial.println("Trying to Reconnect");
  WiFi.begin(ssid, password);
}
