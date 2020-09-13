/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxxxxxxxxx";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "xxxxxxxx";
char pass[] = "xxxxxxxxx";


void output ()
{
  digitalWrite(D3, HIGH);
}

void output1 ()
{
  digitalWrite(D3, LOW);
}

void output2 ()
{
  digitalWrite(D0, HIGH);
}

void output3 ()
{
  digitalWrite(D0, LOW);
}


BLYNK_WRITE(V5) // Button Widget writes to Virtual Pin V5 
{
  if(param.asInt()== 1) {     // if Button sends 1
    output();             // start the function
  }
    if(param.asInt()== 0) {     // if Button sends 1
    output1();             // start the function
  }
}

BLYNK_WRITE(V6) // Button Widget writes to Virtual Pin V5 
{
  if(param.asInt()== 1) {     // if Button sends 1
    output2();             // start the function
  }
    if(param.asInt()== 0) {     // if Button sends 1
    output3();             // start the function
  }
}


BLYNK_WRITE(V7) // Button Widget writes to Virtual Pin V5 
{
    if(param.asInt()== 1) {     // if Button sends 1
    output3();      // start the function 
    output1();
    
  }
}




void setup()
{
  pinMode (D3, OUTPUT);
  pinMode (D0, OUTPUT);
  // Debug console
  Serial.begin(9600);
  
  Blynk.begin(auth, ssid, pass, "blynk.iot-cm.com", 8080); 
  //Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();

}