// C++ code
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int moisture = 0;
int waterval = 0;
int motor = 5;
void setup()
{
  lcd.init();
  lcd.backlight();
  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(motor, OUTPUT);
  Serial.begin(9600);
  
}

void loop()
{
  lcd.setCursor(0,0);
  lcd.print("hello.");
  delay(2000);
  lcd.clear();
  // Apply power to the soil moisture sensor
  digitalWrite(A0, HIGH);
  delay(10); // Wait for 10 millisecond(s)
  moisture = analogRead(A1);
  // Turn off the sensor to reduce metal corrosion
  // over time
  digitalWrite(A0, LOW);
  waterval = digitalRead(2);
  Serial.println(moisture);
  if (moisture < 200) {
    digitalWrite(12, HIGH);
  } else {
    if (moisture < 400) {
      lcd.print("less then 400");
      if(moisture<200)
      lcd.print("less then 200");
    } else {
      if (moisture < 600) {
        lcd.print("less then 600");
        analogWrite(motor, HIGH);
      } else {
        if (moisture < 800) {
          lcd.print("less then 800");
        } else {
          lcd.print("greater then 800");
        }
      }
    }
  }
  delay(3000); // Wait for 100 millisecond(s)
  lcd.clear();
}