int relay = 7;

void setup() {
   pinMode(relay, OUTPUT);
   Serial.begin(9600);
   
}

void loop() {
  
  digitalWrite(relay, HIGH);
  
}