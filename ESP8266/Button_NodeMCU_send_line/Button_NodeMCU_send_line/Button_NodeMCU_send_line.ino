const int led = 5;
const int button = 16;
int temp = 0;
bool Lock = false;

void setup() {
  Serial.begin(112500);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);

}

void loop() {
  temp = digitalRead(button);
     
     if (temp == LOW) {
        digitalWrite(led, HIGH);
        Serial.println("LED Turned ON");
        delay(1000);

       }
     else {
        digitalWrite(led, LOW);
        Serial.println("LED Turned OFF");
        delay(1000);

       }
}
