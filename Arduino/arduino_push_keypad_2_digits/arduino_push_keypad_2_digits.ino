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

char key;
int ckey = 0;
void loop(){  
 

  key = keypad.getKey();// Read the key

if (key != NO_KEY)
{
Serial.println(key);
}

if(ckey == 2){
  if(key == '0'){ //เมื่อ กด 0 เข้าเงื่อนไขนี้
      inputA1 = 1024; // แทนค่า inputA1 ด้วย 1024 ที่ทำให้ PWM มี dutycycle 5 %
      Serial.println(String("Read inputA1 = ")+ inputA1);
  }
  if(key == '1'){ //เมื่อ กด 1 เข้าเงื่อนไขนี้
      inputA1 = 900; // แทนค่า inputA1 ด้วย 900 ที่ทำให้ PWM มี dutycycle 10 %
      Serial.println(String("Read inputA1 = ")+ inputA1);
  }


 ICR1 = 62.5; 
pwm1 = inputA1; 

xxx = float(pwm1);

xxx = xxx * ICR1;

xxx = xxx / 512;

OCR1A = int(62.5-(xxx/2));

  }
}