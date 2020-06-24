#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
int inputA1;

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3}; //connect to the column pinouts of the keypad

//Create an object of keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char key = keypad.getKey();// Read the key
  
  // Print if key pressed
  if (key){
    Serial.print("Key Pressed : ");
    Serial.println(key);
  }

  if(key == '5'){ //เมื่อ กด 5 เข้าเงื่อนไขนี้
      inputA1 = 20; // แทนค่า inputA1 ด้วย 20 ที่ทำให้ PWM มี dutycycle 5 %
    
  }
}
