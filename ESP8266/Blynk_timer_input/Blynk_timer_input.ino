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
char auth[] = "xxxxxxxxxxxxxxx";
char server[] = "oasiskit.com";
char ssid[] = "xxxxxxxxxxxxx";
char pass[] = "xxxxxxxxxxxxx";
int port = 8080;


//====Values WidgetLED=============================
  WidgetLED StatusLED1(V60);
  WidgetLED StatusLED2(V61);
//====END WidgetLED=============================


//====WidgetTimeInput========================================================
//SimpleTimer timer;
char Time[16];
BlynkTimer timer;
WidgetRTC rtc;
WidgetTerminal terminal(V13);
//bool isFirstConnect = true;
long currentTime; 
long TimeStart;
long TimeStop; 

//void requestTime() {
//  Blynk.sendInternal("rtc", "sync");
//}
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

  rtc.begin();
  timer.setInterval(10000L, activetoday);
  timer.setInterval(30000L, reconnectBlynk);
}

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

  //loop Start time
  if (currentTime >= TimeStart){
      terminal.print("Now Time > Start Time");
      terminal.flush();
      if(currentTime <= TimeStart + 30){
        digitalWrite(30, HIGH); //LED On 
        //StatusLED1.on();
        terminal.println("LED ON");
        terminal.flush();
      }
        
  }else{
     /* terminal.print("Now Time < Start Time");
      terminal.flush();*/
      digitalWrite(30, LOW); //LED Off
      terminal.println("LED OFF");
      //StatusLED1.off();
  }
  //// loop End time
    if(currentTime >= TimeStop){
       digitalWrite(30, LOW); // set LED OFF
       terminal.println("LED OFF");
       if(currentTime <= TimeStop){
        digitalWrite(30, LOW); //set LED OFF
        terminal.println("LED OFF");
       }
    }
    else{
       if(currentTime >= TimeStart){
          digitalWrite(30, HIGH); // set LED ON
          terminal.println("LED ON");
       }
    }
 
  // Process timezone
  // Timezone is already added to start/stop time

  //Serial.println(String("Time zone: ") + t.getTZ());

//  for (int i = 1; i <= 7; i++) {
//    if (t.isWeekdaySelected(i)) {
//      Serial.println(String("Day ") + i + " is selected");
//    }else{
//      Serial.println(String("Day ") + i + " is not select");
//    }
//  }

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

}