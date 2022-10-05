#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#define INFLUXDB_URL "https://europe-west1-1.gcp.cloud2.influxdata.com"
#define INFLUXDB_TOKEN "ys8hBxZ5HbjyvRjIsS5y_Mp8FMY1D3QT6E2XXHjfxdnKgqFSDAQfMhNct1h4JhikDatMEVirBGB5ZS-JkmoB-g=="
#define INFLUXDB_ORG "stanutty01@gmail.com"
#define INFLUXDB_BUCKET "ESP32"
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
Point sensor("temp_humi");
#define TZ_INFO "PKT-5"


#if defined(ESP32)
  #include <WiFiMulti.h>
  WiFiMulti wifiMulti;
  #define DEVICE "ESP32"
#elif defined(ESP8266)
  #include <ESP8266WiFiMulti.h>
  ESP8266WiFiMulti wifiMulti;
  #define DEVICE "ESP8266"
#endif

// Uncomment one of the lines below for whatever DHT sensor type you're using!
//#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321





/* DHT */
#include "DHT.h"
#define DHTPIN D0      // what digital pin we're connected to
#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
/********* แสงงง *******/

/**********************/
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <TridentTD_LineNotify.h>
#define LINE_TOKEN "KUdmGZVlBd5RS0vRZSjTJlQMT2fNgGJHAEs35KH9gOk"
#include "SimpleTimer.h"
SimpleTimer timer;
// Replace with your network credentials
const char *ssid = "PCS-Office";
const char *password = "qawsedrf";

String serverName = "http://jaiangelbot.cc.pcs-plp.com/testbot/wtsensor.php";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// Week Days
String weekDays[7] = {"01", "02", "03", "04", "05", "06", "07"};

// Month names
String months[12] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

#include <Ticker.h>
unsigned long previousMillis = 0;
unsigned long previousMillisAlert = 0;
int alertsec = 0, alertm = 0; //นับเวลาฉุกเฉิน หน่วง 10 นาที
int sec = 0, m = 0, h = 0;    //นับเวลาแจ้งเตือนไลน์

float setvalue[] = {300, 400, 500, 50}; //ค่า 1 2 ปกติ 3 และ 4ถ้าเริ่มน้อยแปลว่าให้เช็คเเละเริ่มแจ้งเตือนว่าเเสงน้อย (แสง)
float setvalueh[] = {60, 70}; 
Ticker ticker;
#include <SimpleTimer.h>
SimpleTimer timer;
/*void calsensoer()
{
  int lux = lightMeter.readLightLevel() + 190;
  int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  LINE.notify("Humidity: " + String(h) + "%\t");
  LINE.notify("Lux :" + String(lux) + "%");
}*/
void connectInflux(){
   sensor.addTag("device", DEVICE);
  sensor.addTag("SSID", WiFi.SSID());
  
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");
  
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
  
  }

void setup()
{
   timer.setInterval(1000, temp);
   timer.setInterval(3000, sendinflux);
 // LightSensor.begin();  
//  timer.setInterval(2000, calsensoer);
  Wire.begin();
  LINE.setToken(LINE_TOKEN);
  dht.begin();
  Serial.begin(115200);
 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  connectInflux();

  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(25200);
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}
void sendinflux(){
 sensor.clearFields();
 float humidity = dht.readHumidity();
 float temperature_Celsius = dht.readTemperature();
 sensor.addField("Temperature",temperature_Celsius);
 sensor.addField("Humidity",humidity);
  
  Serial.print("Writing: ");
  Serial.println(client.pointToLineProtocol(sensor));

  // If no Wifi signal, try to reconnect it
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("Wifi connection lost");
  }
  // Write point
  if (!client.writePoint(sensor)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }
  Serial.println("");

}
  

void temp()
{
  
 
  int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  timeClient.update();
  time_t epochTime = timeClient.getEpochTime();
  String formattedTime = timeClient.getFormattedTime();
  int currentHour = timeClient.getHours();
  int currentMinute = timeClient.getMinutes();
  int currentSecond = timeClient.getSeconds();
  String weekDay = weekDays[timeClient.getDay()];
  // Get a time structure
  struct tm *ptm = gmtime((time_t *)&epochTime);
  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon + 1;
  String currentMonthName = months[currentMonth - 1];
  int currentYear = ptm->tm_year + 1900;
  String myString = String(currentYear);
  String dayee = String(currentYear)  +"0"+ String(currentMonth) + String(monthDay)+String(currentHour)+String(currentMinute)+String(currentSecond);
  
  // readtimedate();
  Serial.println(dayee);
  int yearcurrent = myString.toInt();
  int monthcurrent = currentMonthName.toInt();
  int api = (lux * h * (yearcurrent + monthcurrent + monthDay + currentHour + currentMinute + currentSecond) * 7);
  String stringapi = String(api, HEX);
  Serial.println(stringapi);
 /*alertsec = alertm = previousMillisAlert = 0;
  if (currentMillis - previousMillis >= 1000)
  {
     sec++;
      if (sec >= 60)
        m++;
        sec = 0;
      {
        else if(){*/
     
  
              // Check WiFi connection status
              if (WiFi.status() == WL_CONNECTED)
              {
                WiFiClient client;
                HTTPClient http;
                String serverPath = serverName + "?sid=1&light=" + String(lux) + "&hum=" + String(h) + "&times=" + String(myString) + String(currentMonthName) +"0"+ String(monthDay) + String(currentHour) + String(currentMinute) + String(currentSecond) + "&type=alert&key=" + String(stringapi);
                // Your Domain name with URL path or IP address with path
                http.begin(client, serverPath.c_str());
                // Send HTTP GET request
                int httpResponseCode = http.GET();
                if (httpResponseCode > 0)
                {
                  Serial.print("HTTP Response code: ");
                  Serial.println(httpResponseCode);
                  String payload = http.getString();
                  Serial.println(payload);
                }
                else
                {
                  Serial.print("Error code: ");
                  Serial.println(httpResponseCode);
                }
                // Free resources
                http.end();
              }
              else
              {
                Serial.println("WiFi Disconnected");
              }
}
void loop(){
timer.run();
           
            }
    //  } 
        // delay(60000);
  //} 