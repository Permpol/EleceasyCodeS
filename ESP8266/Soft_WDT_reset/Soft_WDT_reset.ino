#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <TridentTD_LineNotify.h>
#include <BlynkSimpleEsp8266.h>
SoftwareSerial NodeSerial(D4, D3); // RX | TX
#define BLYNK_PRINT Serial
#define SSID        "PWAHOME2sd"
#define PASSWORD    "P78991290WA"
#define LINE_TOKEN  "jtJlxIc9ZRMul0mHoKzuFtmj0kSwtDhYx6mPDoTB7uV"
char auth[] = "KWK-5oGEsWYGmJx8xHT8qb8Nn_Pib5jV";
int i_data;
float f_data;
int val;
int input;
int Total;
int Delay;
int ONLINE;
BlynkTimer timer;
WidgetLCD lcd(V7);
WidgetLED led(V8);
WidgetTerminal terminal(V13);
void setup()
{
  pinMode(D3, INPUT);
  pinMode(D4, OUTPUT);
  Serial.begin(9600);
  NodeSerial.begin(57600);
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
 }
  Serial.println(WiFi.localIP());
  LINE.setToken(LINE_TOKEN);
  Blynk.begin(auth, SSID, PASSWORD, "blynk.iot-cm.com", 8080);
  timer.setInterval(1000L, sendUptime); 
}
void loop()
{
  while (NodeSerial.available())
  {
    i_data = NodeSerial.parseInt();
    f_data = NodeSerial.parseFloat();
    Total = i_data + input;    
    terminal.print(i_data);
    terminal.print(" : ");
    terminal.print(input);
    terminal.print(" : ");
    terminal.println(Total);
    delay(Delay);
    Serial.print("รับค่าอนาล็อก");
    Serial.print(" : ");
    Serial.println(Total);
    Blynk.run();
    timer.run();
    Blynk.setProperty(V1,"color","#3d94eb"); //ฟ้า
    Blynk.setProperty(V3,"color","#94eb3d"); //เขียว
    Blynk.setProperty(V5,"color","#3debeb"); // น้ำเงินเข้ม
    Blynk.setProperty(V6,"color","#3DEB94"); // น้ำเงินเข้ม
    if (WiFi.status() != WL_CONNECTED){ reconnect();}
    CheckConnection();
  }
}
void LINE1()
{
  Serial.println("ส่งเเรียบร้อย");
  LINE.notify(Total);
}
BLYNK_WRITE(V1) 
{
 if (param.asInt()==1) {
     ONLINE = 1;
     led.off();
 }else{
     ONLINE = 0;
     led.on();
 }
}
BLYNK_WRITE(V2)
{
  if (param.asInt() == 1){
    if(ONLINE=1)
    {
     LINE1();
     //delay(200);
    }
  }
}
BLYNK_WRITE(V3)
{
  if (param.asInt() == 1){
    LINE1();
    //delay(200);
  }
}
BLYNK_WRITE(V21) //รับค่า+-
{
  input = param.asInt();
  Blynk.virtualWrite(V1, input); 
}
BLYNK_WRITE(V22) //รับค่าหน่วง
{
  Delay = param.asInt();
}
void sendUptime()
{
  Blynk.virtualWrite(V6, Total);
  Blynk.virtualWrite(V5, Total);
}
void reconnect()
{
  Serial.print("Reconnecting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
}
void CheckConnection()   //เช็คการเชือมต่อของ blynk
{
  if(!Blynk.connected())
  {
    Blynk.connect(); 
  }
}
