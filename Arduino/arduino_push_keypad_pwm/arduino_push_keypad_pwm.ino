#include <Keypad.h>

float xxx;
unsigned long pwm1;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
int inputA1;

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2}; //connect to the column pinouts of the keypad

//Create an object of keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  pinMode(9, OUTPUT);
TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1B0) | _BV(WGM11); 
TCCR1B = _BV(WGM13) | _BV(CS11);
  
  Serial.begin(9600);
}
  
void loop(){  
 

  char key = keypad.getKey();// Read the key

  if(key == '0'){ //เมื่อ กด 0 เข้าเงื่อนไขนี้
      inputA1 = 1024; // แทนค่า inputA1 ด้วย 1024 ที่ทำให้ PWM มี dutycycle 5 %
      Serial.println(String("Read inputA1 = ")+ inputA1);
  }
  if(key == '1'){ //เมื่อ กด 1 เข้าเงื่อนไขนี้
      inputA1 = 900; // แทนค่า inputA1 ด้วย 900 ที่ทำให้ PWM มี dutycycle 10 %
      Serial.println(String("Read inputA1 = ")+ inputA1);
  }
  if(key == '2'){ //เมื่อ กด 2 เข้าเงื่อนไขนี้
      inputA1 = 800; // แทนค่า inputA1 ด้วย 800 ที่ทำให้ PWM มี dutycycle 15 %
      Serial.println(String("Read inputA1 = ")+ inputA1);
  }
  if(key == '3'){ //เมื่อ กด 3 เข้าเงื่อนไขนี้
      inputA1 = 700; // แทนค่า inputA1 ด้วย 700 ที่ทำให้ PWM มี dutycycle 20 %
      Serial.println(String("Read inputA1 = ")+ inputA1);
  }
  if(key == '4'){ //เมื่อ กด 4 เข้าเงื่อนไขนี้
      inputA1 = 600; // แทนค่า inputA1 ด้วย 600 ที่ทำให้ PWM มี dutycycle 30 %
      Serial.println(String("Read inputA1 = ")+ inputA1);
  }
  if(key == '5'){ //เมื่อ กด 5 เข้าเงื่อนไขนี้
      inputA1 = 500; // แทนค่า inputA1 ด้วย 500 ที่ทำให้ PWM มี dutycycle 40 %
      Serial.println(String("Read inputA1 = ")+ inputA1);
  }
  if(key == '6'){ //เมื่อ กด 6 เข้าเงื่อนไขนี้
      inputA1 = 400; // แทนค่า inputA1 ด้วย 400 ที่ทำให้ PWM มี dutycycle 50 %
      Serial.println(String("Read inputA1 = ")+ inputA1);
  }
  if(key == '7'){ //เมื่อ กด 7 เข้าเงื่อนไขนี้
      inputA1 = 300; // แทนค่า inputA1 ด้วย 300 ที่ทำให้ PWM มี dutycycle 60 %
      Serial.println(String("Read inputA1 = ")+ inputA1);
  }
  if(key == '8'){ //เมื่อ กด 8 เข้าเงื่อนไขนี้
      inputA1 = 200; // แทนค่า inputA1 ด้วย 200 ที่ทำให้ PWM มี dutycycle 70 %
      Serial.println(String("Read inputA1 = ")+ inputA1);
  }
  if(key == '9'){ //เมื่อ กด 9 เข้าเงื่อนไขนี้
      inputA1 = 100; // แทนค่า inputA1 ด้วย 100 ที่ทำให้ PWM มี dutycycle 80 %
      Serial.println(String("Read inputA1 = ")+ inputA1);
  }
  if(key == '*'){ //เมื่อ กด * เข้าเงื่อนไขนี้
      inputA1 = 50; // แทนค่า inputA1 ด้วย 50 ที่ทำให้ PWM มี dutycycle 90 %
      Serial.println(String("Read inputA1 = ")+ inputA1);
  }
  if(key == '#'){ //เมื่อ กด # เข้าเงื่อนไขนี้
      inputA1 = 0; // แทนค่า inputA1 ด้วย 0 ที่ทำให้ PWM มี dutycycle 100 %
      Serial.println(String("Read inputA1 = ")+ inputA1);
 }

 ICR1 = 62.5; 
pwm1 = inputA1; 

xxx = float(pwm1);

xxx = xxx * ICR1;

xxx = xxx / 512;

OCR1A = int(62.5-(xxx/2));
}