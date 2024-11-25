// C++ code
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int moisture = 0;
int waterval=0;
void setup()
{
  pinMode(2, INPUT);
  Serial.begin(9600);
  
}

void loop()
{
  digitalWrite(A0, LOW);
  waterval = digitalRead(2);
  Serial.println(waterval);
  delay(100);
}
