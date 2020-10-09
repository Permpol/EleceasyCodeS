#define BLYNK_PRINT Serial
#define LINE_TOKEN "6ldCGypYxi8BpiBH1je1g916LRYVjNHrGQrWs1vATVg"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <SPI.h>
#include <TridentTD_LineNotify.h>
#include "Wire.h"
#include <EEPROM.h>
#include <SoftwareSerial.h>
SoftwareSerial NodeSerial(D1, D2); // RX | TX


const int sensorIn = A0;
float mVperAmp = 100; // use 100 for 20A Module and 66 for 30A Module

int X;
int Y;
float TIME = 0;
float FREQUENCY = 0;
float WATER = 0;
float TOTAL = 0;
float LS = 0;
float FlowUnit = 0;
float FlowBath = 0;
float SliderFlow ; 
float Voltage = 0;
float VRMS = 0;
float AmpsRMS = 0;
                                                   
int buttonPin = D0;

int Solenoid = D7;
int Magnetic = D9;
int Flowsensor = D5;
int buttonState = 0;
 char auth[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"; 
 char ssid[] = "Mi Phone";
 char pass[] = "romeo034";

  BLYNK_WRITE(V10)
  {
  SliderFlow = param.asFloat();
  Serial.print(SliderFlow, 3);
  }
  BLYNK_WRITE(V11)
  {
  TOTAL = param.asInt();
  Serial.print(TOTAL);
  }
void setup() 
{
  pinMode(D1, INPUT);
  pinMode(D2, OUTPUT); 
 Serial.begin(9600);
 EEPROM.begin(512);
 NodeSerial.begin(57600);
 EEPROM.get(0, TOTAL);
 Serial.println(TOTAL);
 Serial.println(LINE.getVersion());
 pinMode(Flowsensor,INPUT_PULLUP);

 pinMode(Solenoid,OUTPUT);
 digitalWrite(Solenoid,LOW);

 pinMode(Magnetic, OUTPUT);
 digitalWrite(Magnetic, LOW);

 
 //Blynk.begin(auth, ssid, pass);
 Blynk.begin(auth, ssid, pass, "blynk.en-26.com", 9600);

 // กำหนด Line Token
 LINE.setToken(LINE_TOKEN);

}
void loop() 
{
 Blynk.run();
 while (NodeSerial.available() > 0)
  {
    
    float f_data = NodeSerial.parseFloat();
    if (NodeSerial.read() == '\n')
    {
      Serial.print("AmpsRMS");
      Serial.print(" : ");
      Serial.println(f_data);
    }
  }

 Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707;  //root 2 is 0.707
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 Serial.print(AmpsRMS);
 Serial.println(" Amps RMS");
 Blynk.virtualWrite(V21,AmpsRMS,  " Amps RMS");

  
  NodeSerial.print(AmpsRMS);
  NodeSerial.print("\n");
/*
Blynk.virtualWrite(V25,c2,  " A" );*/


//ส่วนคำนวณอัตราการไหลของน้ำ
X = pulseIn(Flowsensor, HIGH);
Y = pulseIn(Flowsensor, LOW);
TIME = X + Y;
FREQUENCY = 1000000/TIME;
WATER = FREQUENCY/7.5;
LS = WATER/60;
FlowUnit = TOTAL/1000;
FlowBath = FlowUnit*17;

if(FREQUENCY >= 0)
{
if(isinf(FREQUENCY))
{
Serial.print("Water Flow (L/M) >>>> ");
Serial.println(TIME/100);
EEPROM.put(0, TOTAL);// บันทึกค่าตัวแปร
EEPROM.commit();
EEPROM.get(0, TOTAL);
Serial.println(TOTAL);


Blynk.virtualWrite(V13,FlowBath,  " Bath" ); //ส่งค่าปริมาณการใช้น้ำทั้งหมดขึ้นBlynk
Blynk.virtualWrite(V20,TOTAL,  " L" ); //ส่งค่าปริมาณการใช้น้ำทั้งหมดขึ้นBlynk
Blynk.virtualWrite(V12,FlowUnit,  " Unit" ); //ส่งค่าปริมาณการใช้น้ำทั้งหมดขึ้นBlynk
Serial.print("Total Water (L) >>>> ");
Serial.println(TOTAL);
Blynk.virtualWrite(V23,TIME/100,  " L/M" );
}
else
{
TOTAL = TOTAL + LS;
Blynk.virtualWrite(V23,WATER,  " L/M" ); //ส่งค่าอัตราการไหลของน้ำขึ้นBlynk
 //Serial.println(FREQUENCY);
 //Serial.println(WATER);
 //Serial.println(TOTAL);
 Serial.print("Total Water (L) >>>> ");
 Serial.println(TOTAL);
 Serial.print("Water Flow (L/M) >>>> ");
 Serial.println(WATER);
 Blynk.virtualWrite(V22,TOTAL,  "L/H" );
 }

}

 //ตั้งเงื่อนไขของตัวสไลด์ในBlynkเพื่อกำหนดการแจ้งเตือนของLINE
 if (WATER > 0 && WATER < SliderFlow) 
 {
  LINE.notify("มีน้ำรั่ว");
  digitalWrite(Solenoid,HIGH);
 }
 

 /*if (c1 < c2) {
 //LINE.notify("มีกระแสไฟฟ้ารั่ว");
 digitalWrite(Magnetic, HIGH);
 }*/

 
}

float getVPP()
{
  
  float result;
  int readValue = sensorIn;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           //record the maximum sensor value
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           //record the minimum sensor value
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
}