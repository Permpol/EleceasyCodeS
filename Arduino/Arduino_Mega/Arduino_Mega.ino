

#include <Wire.h>             //เรียกใช้ไลบารี่
#include "HX711.h"
#include <LiquidCrystal_I2C.h>           //เรียนใช้ไลบารี่
LiquidCrystal_I2C lcd(0x27, 16, 2);    //กำหนดขนาดจอLCD
//****************** LOAD CELL *************
float calibration_factor = 61281.00; 
#define zero_factor 8268904
#define DOUT  A7
#define CLK   A5
#define DEC_POINT  2
float offset=0;
float get_units_kg();
HX711 scale(DOUT, CLK);


//******************ปุ่มกด**************

//หัวกะทิ
int buttonm1 = 4;
boolean currentm1 = LOW;
boolean lastm1 = LOW;
boolean togglem1 = false;

//หางกะทิ
int buttonm2 = 5;
boolean currentm2 = LOW;
boolean lastm2 = LOW;
boolean togglem2 = false;

//เพิ่มเวลา
int buttonadd = 11;
int buttonStateadd = 0;

//ลบเวลา
int buttonminus = 12;
int buttonStateminus = 0;


//Start
int buttonstart = 10;
int buttonStatestart = 0;
//Stop
int buttonstop = 3;
int buttonStatestop = 0;

//Start - Stop
int buttonfree = 6;
boolean currentfree = LOW;
boolean lastfree = LOW;
boolean togglefree = false;

//****************** RELAY **************
int relay = 9;
int relayState = LOW; 
int relay2 = 8;
int relayState2 = LOW; 

//********** MENU : หัวกะทิ ***********
float hu1 = 0.2 ;
float hu2 = 0.3 ;
float hu3 = 0.4 ;
float hu4 = 0.5 ;
float hu5 = 0.6 ;
float hu6 = 0.7 ;
float hu7 = 0.8 ;
float hu8 = 0.9 ;
float hu9 = 1.0 ;
float hu10 = 1.1 ;
float hu11 = 1.2 ;
float hu12 = 1.3 ;
float hu13 = 1.4 ;
float hu14 = 1.5 ;
float hu15 = 1.6 ;
float hu16 = 1.7 ;
float hu17 = 1.8 ;
float hu18 = 1.9 ;
float hu19 = 2.0 ;
float hu20 = 2.1 ;
float hu21 = 2.2 ;
float hu22 = 2.3 ;
float hu23 = 2.4 ;
float hu24 = 2.5 ;
//********** หางกะทิ ***********
float ha1 = 0.5 ;
float ha2 = 0.7 ;
float ha3 = 0.8 ;
float ha4 = 1.0 ;
float ha5 = 1.1 ;
float ha6 = 1.2 ;
float ha7 = 1.3 ;
float ha8 = 1.4 ;
float ha9 = 1.5 ;
float ha10 = 1.6 ;
float ha11 = 1.7 ;
float ha12 = 1.8 ;
float ha13 = 1.9 ;
float ha14 = 2.0 ;
float ha15 = 2.1 ;
float ha16 = 2.2 ;
float ha17 = 2.3 ;
float ha18 = 2.4 ;
float ha19 = 2.5 ;
float ha20 = 2.6 ;
float ha21 = 2.7 ;
float ha22 = 2.8 ;
float ha23 = 2.9 ;
float ha24 = 3.0 ;
float ha25 = 3.1 ;
float ha26 = 3.2 ; 
float ha27 = 3.3 ; 
float ha28 = 3.4 ; 

//****************** ตัวแปร **************

float cas ;
float w ;
float liter  ;
float TOTAL ;
//******************************************
//****************** Water flow **************
volatile double waterFlow;
//********************************************


void loadkg() {
  
  Serial.print(" ");
  String data = String(get_units_kg()+offset, DEC_POINT);
  Serial.print(data);
  Serial.println(" kg");
  delay(100);
}
float get_units_kg()
{
  return(scale.get_units()*0.453592);
}


void setup() 
{
  Serial.begin(9600);

 
 waterFlow = 0;
 attachInterrupt(4, pulse, RISING); //DIGITAL Pin 2: Interrupt 0
  
  scale.set_scale(calibration_factor); 
  scale.set_offset(zero_factor);    
  pinMode(buttonm1, INPUT);
  pinMode(buttonadd, INPUT);
  pinMode(buttonfree, INPUT);
  pinMode(relay, OUTPUT); 
  pinMode(relay2, OUTPUT); 
  digitalWrite(relay, HIGH);
  digitalWrite(relay2, HIGH);
    lcd.begin();  //กำหนดค่าเริ่มต้นLCD
    lcd.setCursor(0, 0);  // เซต ตำแหน่งคำ 0,0
    lcd.print("WELCOME ");
    lcd.setCursor(0, 1);  // เซต ตำแหน่งคำ 0,0
    lcd.print("SELECT MENU");
    Serial.println("--------------------------------");
    Serial.println("*** WELCOME ***");
    Serial.println("--------------------------------");
    delay(100);   //สั่งดีย์เลย์ เท่ากับ 3วิ    
    Serial.println(" MAIN MENU : กรุณากดปุ่ม ");

  
}


//แดง ดำ ขาว เขียว 
void loop() 
{ 
  w = get_units_kg();
  //cas = liter;

//***********************************************************************************************



//****************************************** ปุ่มกด เลือกโหมด ***************************************
  
  currentm1 = digitalRead(buttonm1);
  if (currentm1 == HIGH && lastm1 == LOW) { //if button has just been pressed    
    togglem1 = !togglem1;
    if (togglem1 == true) {
      Serial.println(" ปิด Mode 1  ");
      lcd.setCursor(0, 0);  //เซตค่าตำแหน่งแถวที่ 3บรรทัด0
      lcd.print("    MAIN MODE   ");  //แสดงคำนี้ออกไป 1
                    //   lcd.setCursor(0, 1);   //เซตค่าตำแหน่งแถวที่ 0บรรทัด1
               // lcd.print("   SELECT MENU    ");  //แสดงคำนี้ออกไป 1  
      lcd.print(w);

      
      //loadkg();
    } else {
      lcd.setCursor(0, 0);  //เซตค่าตำแหน่งแถวที่ 3บรรทัด0
      lcd.print("MODE 1 (Wt):");  //แสดงคำนี้ออกไป 1
      lcd.print(w);
      lcd.setCursor(0, 1);  //เซตค่าตำแหน่งแถวที่ 3บรรทัด0
      lcd.print("WATER ");  //แสดงคำนี้ออกไป 1
      Serial.println(" เปิด Mode 1 ");
      Serial.print("ชั่งน้ำหนักได้ : ");
      Serial.println(w);
      //waterFlow = 0;
      
         if (w > 0.1 && w  < 0.5 )
            {
              cas = hu1;
              Serial.println(" MODE 1 : ควรใส่น้ำ 0.2 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
              
               

            }
            
         if (w > 0.5 && w  < 0.7 )
            {
              cas = hu2;
              Serial.println(" MODE 1 : ควรใส่น้ำ 0.3 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
               
              
 
            }
            
          if (w > 0.7 && w  < 0.9 )
            {
              cas = hu3;
              Serial.println(" MODE 1 : ควรใส่น้ำ 0.4 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
          

            }

          if (w > 0.9 && w  < 1.0 )
            {
              cas = hu4;
              Serial.println(" MODE 1 : ควรใส่น้ำ 0.5 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
               lcd.print(cas);

            }

          if (w > 1.0 && w  < 1.2 )
            {
              cas = hu5;
              Serial.println(" MODE 1 : ควรใส่น้ำ 0.6 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
               lcd.print(cas);
          

            }

           if (w > 1.2 && w  < 1.4 )
            {
              cas = hu6;
              Serial.println(" MODE 1 : ควรใส่น้ำ 0.7 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
               lcd.print(cas);
              

            }

           if (w > 1.4 && w  < 1.6 )
            {
              cas = hu7;
              Serial.println(" MODE 1 : ควรใส่น้ำ 0.8 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
               lcd.setCursor(7, 1);
                 lcd.print(cas);
               
            }
           
           if (w > 1.6 && w  < 1.8 )
            {
              cas = hu8;
              Serial.println(" MODE 1 : ควรใส่น้ำ 0.9 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
                 lcd.print(cas);
               
            }

            if (w > 1.8 && w  < 2.0 )
            {
              cas = hu9;
              Serial.println(" MODE 1 : ควรใส่น้ำ 1.0 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
                 lcd.print(cas);
              
            }

            if (w > 2.0 && w  < 2.3 )
            {
              cas = hu10;
              Serial.println(" MODE 1 : ควรใส่น้ำ 1.1 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }

             if (w > 2.3 && w  < 2.6 )
            {
              cas = hu11;
              Serial.println(" MODE 1 : ควรใส่น้ำ 1.2 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
            
            if (w > 2.6 && w  < 2.8 )
            {
              cas = hu12;
              Serial.println(" MODE 1 : ควรใส่น้ำ 1.3 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
            
            if (w > 2.8 && w  < 3.0 )
            {
              cas = hu13;
              Serial.println(" MODE 1 : ควรใส่น้ำ 1.4 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }

            if (w > 3.0 && w  < 3.3 )
            {
              cas = hu14;
              Serial.println(" MODE 1 : ควรใส่น้ำ 1.5 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }

            if (w > 3.3 && w  < 3.5)
            {
              cas = hu15;
              Serial.println(" MODE 1 : ควรใส่น้ำ 1.6 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }

            if (w > 3.5 && w  < 3.7)
            {
              cas = hu16;
              Serial.println(" MODE 1 : ควรใส่น้ำ 1.7 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }

            if (w > 3.7 && w  < 3.9)
            {
              cas = hu17;
              Serial.println(" MODE 1 : ควรใส่น้ำ 1.8 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
            
            if (w > 3.9 && w  < 4.0)
            {
              cas = hu18;
              Serial.println(" MODE 1 : ควรใส่น้ำ 1.9 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
            
            if (w > 4.0 && w  < 4.2)
            {
              cas = hu19;
              Serial.println(" MODE 1 : ควรใส่น้ำ 2.0 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
            
            if (w > 4.2 && w  < 4.4)
            {
              cas = hu20;
              Serial.println(" MODE 1 : ควรใส่น้ำ 2.1 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }

            if (w > 4.4 && w  < 4.6)
            {
              cas = hu21;
              Serial.println(" MODE 1 : ควรใส่น้ำ 2.2 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }

            if (w > 4.6 && w  < 4.8)
            {
              cas = hu22;
              Serial.println(" MODE 1 : ควรใส่น้ำ 2.3 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
            
            if (w > 4.8 && w  < 4.9)
            {
              cas = hu23;
              Serial.println(" MODE 1 : ควรใส่น้ำ 2.4 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }

            if (w > 4.9 && w  < 5.0)
            {
              cas = hu24;
              Serial.println(" MODE 1 : ควรใส่น้ำ 2.5 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }


            
    }
    delay(1);
  } else if (currentm1 == LOW && lastm1 == HIGH) {
    delay(1);
  }
  lastm1 = currentm1;


  
  currentm2 = digitalRead(buttonm2);
  if (currentm2 == HIGH && lastm2 == LOW) { //if button has just been pressed    
    togglem2 = !togglem2;
    if (togglem2 == true) {
     Serial.println(" ปิด MODE 2 ");
      lcd.setCursor(0, 0);  //เซตค่าตำแหน่งแถวที่ 3บรรทัด0
      lcd.print("    MAIN MODE   ");  //แสดงคำนี้ออกไป 1
                   //    lcd.setCursor(0, 1);   //เซตค่าตำแหน่งแถวที่ 0บรรทัด1
             //   lcd.print("   SELECT MENU    ");  //แสดงคำนี้ออกไป 1  
      lcd.print(w);
      lcd.setCursor(0, 1);  //เซตค่าตำแหน่งแถวที่ 3บรรทัด0
      lcd.print("              ");  //แสดงคำนี้ออกไป 1
    } else {
      lcd.setCursor(0, 0);  //เซตค่าตำแหน่งแถวที่ 3บรรทัด0
      lcd.print("MODE 2 (Wt):");  //แสดงคำนี้ออกไป 1
      lcd.print(w);
      lcd.setCursor(0, 1);  //เซตค่าตำแหน่งแถวที่ 3บรรทัด0
      lcd.print("WATER ");  //แสดงคำนี้ออกไป 1
      Serial.println(" เปิด Mode 2 ");
      Serial.print("ชั่งน้ำหนักได้ : ");
      Serial.println(w);
      //waterFlow = 0;
      
         if (w > 0.1 && w  < 0.5 )
         
            {
              cas = ha1;
              Serial.println(" MODE 2 : ควรใส่น้ำ 0.5 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
            
         if (w > 0.5 && w  < 0.8 )
            {
              cas = ha2;
              Serial.println(" MODE 2 : ควรใส่น้ำ 0.7 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                        
         if (w > 0.8 && w  < 0.9 )
            {
              cas = ha3;
              Serial.println(" MODE 2 : ควรใส่น้ำ 0.8 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                    
         if (w > 0.9 && w  < 1.0 )
            {
              cas = ha4;
              Serial.println(" MODE 2 : ควรใส่น้ำ 1.0 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                
         if (w > 1.0 && w  < 1.2 )
            {
              cas = ha5;
              Serial.println(" MODE 2 : ควรใส่น้ำ 1.1 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                            
         if (w > 1.2 && w  < 1.3 )
            {
              cas = ha6;
              Serial.println(" MODE 2 : ควรใส่น้ำ 1.2 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                                        
         if (w > 1.3 && w  < 1.5 )
            {
              cas = ha7;
              Serial.println(" MODE 2 : ควรใส่น้ำ 1.3 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                                                    
         if (w > 1.5 && w  < 1.7 )
            {
              cas = ha8;
              Serial.println(" MODE 2 : ควรใส่น้ำ 1.4 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                                                                
         if (w > 1.7 && w  < 1.8 )
            {
              cas = ha9;
              Serial.println(" MODE 2 : ควรใส่น้ำ 1.5 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                                                                            
         if (w > 1.8 && w  < 1.9 )
            {
              cas = ha10;
              Serial.println(" MODE 2 : ควรใส่น้ำ 1.6 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                                                                                        
         if (w > 1.9 && w  < 2.0 )
            {
              cas = ha11;
              Serial.println(" MODE 2 : ควรใส่น้ำ 1.7 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
            
                                                                                                                                    
         if (w > 2.0 && w  < 2.2 )
            {
              cas = ha12;
              Serial.println(" MODE 2 : ควรใส่น้ำ 1.8 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                                                                                                                
         if (w > 2.2 && w  < 2.4 )
            {
              cas = ha13;
              Serial.println(" MODE 2 : ควรใส่น้ำ 1.9 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                                                                                                                            
         if (w > 2.4 && w  < 2.6 )
            {
              cas = ha14;
              Serial.println(" MODE 2 : ควรใส่น้ำ 2.0 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                                                                                                                                        
         if (w > 2.6 && w  < 2.8 )
            {
              cas = ha15;
              Serial.println(" MODE 2 : ควรใส่น้ำ 2.1 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                                                                                                                                                    
         if (w > 2.8 && w  < 2.9 )
            {
              cas = ha16;
              Serial.println(" MODE 2 : ควรใส่น้ำ 2.2 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                                                                                                                                                                
         if (w > 2.9 && w  < 3.0 )
            {
              cas = ha17;
              Serial.println(" MODE 2 : ควรใส่น้ำ 2.3 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                                                                                                                                                                            
         if (w > 3.0 && w  < 3.1 )
            {
              cas = ha18;
              Serial.println(" MODE 2 : ควรใส่น้ำ 2.4 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }

                                                                                                                                                                                                                        
         if (w > 3.1 && w  < 3.3 )
            {
              cas = ha19;
              Serial.println(" MODE 2 : ควรใส่น้ำ 2.5 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
            
                                                                                                                                                                                                                                    
         if (w > 3.3 && w  < 3.5 )
            {
              cas = ha20;
              Serial.println(" MODE 2 : ควรใส่น้ำ 2.6 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                                                                                                                                                                                                                
         if (w > 3.5 && w  < 3.7 )
            {
              cas = ha21;
              Serial.println(" MODE 2 : ควรใส่น้ำ 2.7 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                                                                                                                                                                                                                            
         if (w > 3.7 && w  < 3.8 )
            {
              cas = ha22;
              Serial.println(" MODE 2 : ควรใส่น้ำ 2.8 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }

                                                                                                                                                                                                                                                                        
         if (w > 3.8 && w  < 4.0 )
            {
              cas = ha23;
              Serial.println(" MODE 2 : ควรใส่น้ำ 2.9 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              Serial.println(TOTAL);
              lcd.print(cas);
            }
            
                                                                                                                                                                                                                                                                        
         if (w > 4.0 && w  < 4.2 )
            {
              cas = ha24;
              Serial.println(" MODE 2 : ควรใส่น้ำ 3.0 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                                                                                                                                                                                                                                                    
         if (w > 4.2 && w  < 4.4 )
            {
              cas = ha25;
              Serial.println(" MODE 2 : ควรใส่น้ำ 3.1 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }

                                                                                                                                                                                                                                                                                              
         if (w > 4.4 && w  < 4.6 )
            {
              cas = ha26;
              Serial.println(" MODE 2 : ควรใส่น้ำ 3.2 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
                                                                                                                                                                                                                                                                                                          
         if (w > 4.6 && w  < 4.8 )
            {
              cas = ha27;
              Serial.println(" MODE 2 : ควรใส่น้ำ 3.3 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }
         if (w > 4.8 && w  < 5.0 )
            {
              cas = ha28;
              Serial.println(" MODE 2 : ควรใส่น้ำ 3.4 ลิตร ");
              Serial.print(" Water to Use : ");
              Serial.println(cas);
              lcd.print(cas);
            }



      
    }
    delay(1);
  } else if (currentm2 == LOW && lastm2 == HIGH) {
    delay(1);
  }
  lastm2 = currentm2;
  
  //****************************** เพิ่มลดค่า ***************************** 
  
  buttonStateadd = digitalRead(buttonadd);
  if(buttonStateadd == LOW ) {   
    
   liter = cas + 0.1;
   cas = liter;
   Serial.print("เพิ่มจำนวนลิตรครั้งละ 0.1 :  ");
   Serial.println(liter);
   Serial.print("CAS :  ");
   Serial.println(cas);
   lcd.setCursor(11, 1);  // เซต ตำแหน่งคำ 0,0
   lcd.print(liter);
   delay (100);
  }


  buttonStateminus = digitalRead(buttonminus);
  if(buttonStateminus == LOW ) {   
    
   liter = cas - 0.1;
   cas = liter;
   
   Serial.print("ลดจำนวนลิตรครั้งละ 0.1 :  ");
   Serial.println(liter);
   Serial.print("CAS :  ");
   Serial.println(cas);
   lcd.setCursor(11, 1);  // เซต ตำแหน่งคำ 0,0
   lcd.print(liter);
   delay (100);
  }

   // lcd.setCursor(0, 0);  // เซต ตำแหน่งคำ 0,0
   // lcd.print("WELCOME ");
   // lcd.setCursor(0, 1);  // เซต ตำแหน่งคำ 0,0

//***************************************************************************************



  //******************************* เริ่มทำงานควบคุมปั๊ม ***************************************  


          buttonStatestart = digitalRead(buttonstart);
            if(buttonStatestart == LOW ) {   
             Serial.println("เปิดปั๊มน้ำแล้ว");
             Serial.print("ค่าที่ต้องการ");
             Serial.println(cas);
              lcd.setCursor(0, 0);  //เซตค่าตำแหน่งแถวที่ 3บรรทัด0
              lcd.print("   - WORKING -    ");  //แสดงคำนี้ออกไป 1
              lcd.setCursor(0, 1);   //เซตค่าตำแหน่งแถวที่ 0บรรทัด1
              lcd.print("                   ");  //แสดงคำนี้ออกไป 1
              Setpump1on();    
          }

          /*
          if ( TOTAL >= cas)
               { 
                                               
            //  lcd.setCursor(0, 0);  //เซตค่าตำแหน่งแถวที่ 3บรรทัด0
            //  lcd.print("                  ");  //แสดงคำนี้ออกไป 1
            //  lcd.setCursor(0, 1);   //เซตค่าตำแหน่งแถวที่ 0บรรทัด1
            //  lcd.print("    SUCCESS    ");  //แสดงคำนี้ออกไป 1       
                Serial.print("น้ำเพียงพอ ปิดปั๊มแล้ว");
                Serial.println(liter);
                Serial.print("ค่าที่ต้องการ");
                Serial.println(cas);
                digitalWrite(relay, HIGH);                     
                //TOTAL  = 0 ;   
                //liter  = 0 ;     
             
                delay(300);     
                  
               }    
               */  
//******************************************************************************************

//******************************* หยุดการทำงาน ************************************************  


          buttonStatestop = digitalRead(buttonstop);
            if(buttonStatestop == LOW ) {   
             Serial.println("ปิดปั๊มน้ำแล้ว");
              lcd.setCursor(0, 0);  //เซตค่าตำแหน่งแถวที่ 3บรรทัด0
              lcd.print("     - STOP -    ");  //แสดงคำนี้ออกไป 1
              lcd.setCursor(0, 1);   //เซตค่าตำแหน่งแถวที่ 0บรรทัด1
              lcd.print("                   ");  //แสดงคำนี้ออกไป 1
              Setpump1off();   
            
          }
            else  
               {                                                               
                Serial.print(" ");                       
                delay(300);     
                  
               } 
//**********************************************************************************************
//*************************************************************************************************





//***************************************** FREE BUTTON *****************************************
 currentfree = digitalRead(buttonfree);
  if (currentfree == HIGH && lastfree == LOW) { //if button has just been pressed
 
    togglefree = !togglefree;
    if (togglefree == true) {
      Serial.println(" Stop FREE ");
      Setpump2off();
      
    } else {
      Serial.println(" Start FREE ");
      digitalWrite(relay2, LOW); 
      Setpump2on();
    }
    Serial.println(" ");
    delay(1);
  } else if (currentfree == LOW && lastfree == HIGH) {
 
    Serial.println(" ");
    delay(1);
  }
  lastfree = currentfree;

//************************************************************************************************

//************************************* TEST ***************************************************
/*
                currentt = digitalRead(buttont);
                if (currentt == HIGH && lastt == LOW) 
                        {
                    togglet = !togglet;
                if (togglet == true) {
                  
                    Serial.println("PUMP - ON");
                      lcd.setCursor(0, 0);  //เซตค่าตำแหน่งแถวที่ 3บรรทัด0
                      lcd.print("  - WORKING -    ");  //แสดงคำนี้ออกไป 1
                      lcd.setCursor(0, 1);   //เซตค่าตำแหน่งแถวที่ 0บรรทัด1
                      lcd.print(" PUMP - ON ");           
                      digitalWrite(relay, HIGH);
                    
                        } 
                else 
                        {
                    Serial.println("PUMP - OFF");
                      lcd.setCursor(0, 1);   //เซตค่าตำแหน่งแถวที่ 0บรรทัด1
                      lcd.print(" PUMP - OFF ");  
                      digitalWrite(relay, LOW); 

                               
                       }
                    Serial.println("Pressed");
                    delay(1);
                        } 
                else if (currentt == LOW && lastt == HIGH) 
                        {
                    Serial.println("Released");
                    delay(1);
                    }
                    lastt = currentt;
  */     
//***********************************************************************************************         


           
                          if ( waterFlow >= liter )
                             { 
                                      
                                // lcd.setCursor(0, 0);  //เซตค่าตำแหน่งแถวที่ 3บรรทัด0
                                // lcd.print("                  ");  //แสดงคำนี้ออกไป 1
                                // lcd.setCursor(0, 1);   //เซตค่าตำแหน่งแถวที่ 0บรรทัด1
                                // lcd.print("   SELECT MENU    ");  //แสดงคำนี้ออกไป 1           
                                  Serial.print(" ปิดปั๊มแล้ว");
                                  Serial.println(liter);
                                  Setpump1off();                   
                                  TOTAL  = 0 ;   
                                  liter  = 0 ; 
                          
                                  waterFlow = 0;   
                                  delay(300);       
                           } 
       

//***********************************************************************

   Serial.print("waterFlow:");
 Serial.print(waterFlow);
 Serial.println(" L");
 delay(500);
}

void Setpump1off()
{
  digitalWrite(relay, HIGH);
}

void Setpump1on()
{
  digitalWrite(relay, LOW);
}
void Setpump2off()
{
  digitalWrite(relay2, HIGH);
}

void Setpump2on()
{
  digitalWrite(relay2, LOW);
}



void pulse() //measure the quantity of square wave
{
 waterFlow += 1.0 / 5880.0;
}
