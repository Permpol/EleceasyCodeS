  ///// set button 1 ///
 #include <TridentTD_LineNotify.h>

#define SSID        "Eleceasy"
#define PASSWORD    "Bb20072536"
#define LINE_TOKEN  "DNi0g1Q9WuiBqhfTmKaHQWQdXXfIQ6qC0fpaH6MfJsu"
const int led = 5;
const int button = 16;
int temp = 0;
bool Lock = false;

void setup() {
  Serial.begin(112500);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  Serial.println(LINE.getVersion());
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);

  // ตัวอย่างส่งข้อความ
  LINE.notify(String("Send to easyDemo ") + 10);

  // ตัวอย่างส่งข้อมูล ตัวเลข
  //LINE.notify(2342);          // จำนวนเต็ม
  //LINE.notify(212.43434,5);   // จำนวนจริง แสดง 5 หลัก

  // เลือก Line Sticker ได้จาก https://devdocs.line.me/files/sticker_list.pdf
  //LINE.notifySticker(3,240);        // ส่ง Line Sticker ด้วย PackageID 3 , StickerID 240
  //LINE.notifySticker("Hello",1,2);  // ส่ง Line Sticker ด้วย PackageID 1 , StickerID 2  พร้อมข้อความ

  // ตัวอย่างส่ง รูปภาพ ด้วย url
  //LINE.notifyPicture("https://preview.ibb.co/j6G51n/capture25610417181915334.png");
  //LINE.notifyPicture("จตุธาตุ","https://www.fotoaparat.cz/storage/pm/09/10/23/670915_a5351.jpg");
}

void loop() {
  temp = digitalRead(button);
     
     if (temp == LOW) {
      if(Lock == true){
        digitalWrite(led, HIGH);
        Serial.println("LED Turned ON");
        LINE.notify("LED ON");
        delay(1000);
        Lock = false;
      }
       }
     else {
      if(Lock == false){
        digitalWrite(led, LOW);
        Serial.println("LED Turned OFF");
        LINE.notify("LED OFF");
        delay(1000);
        Lock = true;
      }
       }
}
