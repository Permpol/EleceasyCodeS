//  LIBRARY
//====================================================
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#define EspSerial Serial3
#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);
#include <TimeLib.h>
#include <WidgetRTC.h>
#include <EEPROM.h>

//====================================================

//  DEKLARASI AWAL
//====================================================
char auth[] = "CY5tqu1d8NmgXUcTC9HFpqCkJMe2Yq8R";
char server[] = "oasiskit.com";
char ssid[] = "Office2.4G";
char pass[] = "glnvdgdj'";
int port = 8080;


//====Values WidgetLED=============================
  WidgetLED StatusLED1(V60);
  WidgetLED StatusLED2(V61);
//====END WidgetLED=============================

//=============================
char Time[16];
BlynkTimer timer;
WidgetRTC rtc;
WidgetTerminal terminal(V13);
bool isFirstConnect = true;
long currentTime; 
long TimeStart;
long TimeStop; 
String displaycurrenttimepluswifi;
//=============================

void setup()
{
  pinMode(30, OUTPUT);
  pinMode(32, OUTPUT);

  digitalWrite(30, LOW);
  digitalWrite(32, LOW);
  
  Serial.begin(115200);
  Serial3.begin(115200);

  delay(10);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  //WiFi.begin(ssid, pass); //เชื่อมต่อ WiFi
  Blynk.begin(auth, wifi, ssid, pass, server, port);     //Reguler server
  //Blynk.begin(auth, wifi, ssid, pass, "192.168.43.120", 8080);    //Local server
  terminal.clear();
  
  int mytimeout = millis() / 1000;
  while (Blynk.connect() == false) { // try to connect to server for 10 seconds
    if ((millis() / 1000) > mytimeout + 8) { // try local server if not connected within 9 seconds
      break;
    }
  }
  
  rtc.begin();
  timer.setInterval(10000L, activetoday);
  timer.setInterval(30000L, reconnectBlynk);
  timer.setInterval(5000L, clockvalue);  // check value for time
}

//====WidgetTimeInput========================================================
BLYNK_CONNECTED() {
  if (isFirstConnect) {
    Blynk.syncAll();
    Blynk.notify("TIMER STARTING!!!!");
    isFirstConnect = false;
  }
}


void clockvalue() // Show time on Terminal
{
  int gmthour = hour();
  if (gmthour == 24) {
    gmthour = 0;
  }
  String displayhour =   String(gmthour, DEC);
  int hourdigits = displayhour.length();
  if (hourdigits == 1) {
    displayhour = "0" + displayhour;
  }
  String displayminute = String(minute(), DEC);
  int minutedigits = displayminute.length();
  if (minutedigits == 1) {
    displayminute = "0" + displayminute;
  }

  displaycurrenttimepluswifi = "Clock:  " + displayhour + ":" + displayminute + " ";
  Blynk.setProperty(V13, "label", displaycurrenttimepluswifi);

}



//====End TimeInput========================================================


//====LED1================================================

BLYNK_WRITE(V2) {
  //Debug
  Serial.print("Got a valueLED1: ");
  Serial.println(param.asInt());
  
  if (param.asInt()) {
    digitalWrite(30, HIGH);
    StatusLED1.on();
    terminal.println("Turn on LED1");
    terminal.flush();
  }
  else {
    digitalWrite(30, LOW);
    StatusLED1.off();
    terminal.println("Turn off LED1");
    terminal.flush();
  }
}
//====END LED1===============================================

//====LED 2================================================

BLYNK_WRITE(V3) {
  //Debug
  Serial.print("Got a valueLED2: ");
  Serial.println(param.asInt());
  
  if (param.asInt()) {
    digitalWrite(32, HIGH);
    StatusLED2.on();
    terminal.println("Turn on LED2");
    terminal.flush();
  }
  else {
    digitalWrite(32, LOW);
    StatusLED2.off();
    terminal.println("Turn off LED2");
    terminal.flush();
  }
}
//====END LED2================================================


void activetoday() {       // check if schedule should run today
  if (year() != 1970) {    
      Blynk.syncVirtual(V20); // sync timeinput widget
      Blynk.sendInternal("rtc", "sync");
  }
}


BLYNK_WRITE(V20){
  sprintf(Time, "%02d:%02d:%02d", hour(), minute(), second());
  Serial.print("Time : ");
  Serial.println(Time);
  TimeInputParam t(param);
  
  currentTime = ((hour() * 3600) + (minute() * 60));
  Serial.print("Time Now : ");
  Serial.println(currentTime);
  
  TimeStart = (t.getStartHour() * 3600) + (t.getStartMinute() * 60);
  Serial.print("Time Start : ");
  Serial.println(TimeStart);

  TimeStop = (t.getStopHour() * 3600) + (t.getStopMinute() * 60);

  //ตรวจสอบการเลือกวัน
    int dayadjustment = -1;
    if (weekday() == 1) {
      dayadjustment =  6; 
    }
    if (t.isWeekdaySelected(weekday() + dayadjustment)) { 

      for (int i = 1; i <= 7; i++) {  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
        if (t.isWeekdaySelected(i)) {
          terminal.println(String("Day ") + i + " is selected");
          terminal.flush();
          
          if(currentTime >= TimeStart && currentTime < TimeStop){
            terminal.print("LED ON");
            terminal.flush();
            digitalWrite(30,HIGH);
            digitalWrite(32,HIGH);
            StatusLED1.on();
            StatusLED2.on();
          }else{
            terminal.print("LED OFF");
            terminal.flush();
            digitalWrite(30,LOW);
            digitalWrite(32,LOW);
            StatusLED1.off();
            StatusLED2.off();
          }
          
        }
      }
    }
    else {
      ///Not Day Select
    }

}

void reconnectBlynk() {
  if (!Blynk.connected()) {
    if (Blynk.connect()) {
      BLYNK_LOG("Reconnected");
    } else {
      BLYNK_LOG("Not reconnected");
    }
  }
}

void loop()
{
  Blynk.run();
  if ( Serial3.available() )   {
    Serial.write( Serial3.read() );
  }
  if ( Serial.available() )       {
    Serial3.write( Serial.read() );
  }
  timer.run();
}