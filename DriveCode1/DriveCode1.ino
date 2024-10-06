#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// For exhaust fan
#define FAN_PIN 6  // No semicolon here

// Define the LCD address and initialize the library
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 columns, 2 rows

// Define relay pins
const int relayPins[] = { 2, 3, 4, 5 };
const int numRelays = 4;

// Define LED pins
const int redLedPin = 10;
const int greenLedPin = 9;

// Relay states
bool relayState[numRelays] = { false, false, false, false };

// Master relay state
bool masterRelayState = false;

// Lowest and highest sensor readings
const int sensorMin = 0;     // Sensor minimum
const int sensorMax = 1024;  // Sensor maximum

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.backlight();

  // Initialize relay and LED pins
  for (int i = 0; i < numRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH);  // Relays are typically active LOW
  }
  
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, LOW);

  // Initialize serial communication
  Serial.begin(9600);

  // Display initial status
  updateDisplay();
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    switch (command) {
      case '1':
        masterRelayState = true;
        relayState[0] = true;
        digitalWrite(relayPins[0], LOW);  // Master relay ON
        digitalWrite(redLedPin, LOW);
        digitalWrite(greenLedPin, HIGH);
        Serial.println("Master Relay ON");
        break;
      case '2':
        if (masterRelayState) {
          relayState[1] = true;
          digitalWrite(relayPins[1], LOW);  // Relay 2 ON
          Serial.println("Relay 2 ON");
        } else {
          Serial.println("Cannot turn ON Relay 2, Master Relay is OFF");
        }
        break;
      case '3':
        if (masterRelayState) {
          relayState[2] = true;
          digitalWrite(relayPins[2], LOW);  // Relay 3 ON
          Serial.println("Relay 3 ON");
        } else {
          Serial.println("Cannot turn ON Relay 3, Master Relay is OFF");
        }
        break;
      case '4':
        if (masterRelayState) {
          relayState[3] = true;
          digitalWrite(relayPins[3], LOW);  // Relay 4 ON
          Serial.println("Relay 4 ON");
        } else {
          Serial.println("Cannot turn ON Relay 4, Master Relay is OFF");
        }
        break;
      case 'q':
        masterRelayState = false;
        relayState[0] = false;
        digitalWrite(relayPins[0], HIGH);  // Master relay OFF
        digitalWrite(redLedPin, HIGH);
        digitalWrite(greenLedPin, LOW);
        Serial.println("Master Relay OFF");
        // Turn off all other relays
        for (int i = 1; i < numRelays; i++) {
          relayState[i] = false;
          digitalWrite(relayPins[i], HIGH);  // Turn off relay
        }
        Serial.println("All other relays OFF");
        break;
      case 'w':
        relayState[1] = false;
        digitalWrite(relayPins[1], HIGH);  // Relay 2 OFF
        Serial.println("Relay 2 OFF");
        break;
      case 'e':
        relayState[2] = false;
        digitalWrite(relayPins[2], HIGH);  // Relay 3 OFF
        Serial.println("Relay 3 OFF");
        break;
      case 'r':
        relayState[3] = false;
        digitalWrite(relayPins[3], HIGH);  // Relay 4 OFF
        Serial.println("Relay 4 OFF");
        break;
      default:
        Serial.println("Invalid Command");
        break;
    }

    updateDisplay();

    // Handle blinking "NO POWER SUPPLY" when master relay is OFF
    if (!masterRelayState) {
      static unsigned long lastBlinkTime = 0;
      static bool blinkState = false;

      unsigned long currentMillis = millis();
      if (currentMillis - lastBlinkTime >= 500) {  // Blink every 500 milliseconds
        lastBlinkTime = currentMillis;
        blinkState = !blinkState;  // Toggle the blink state
        if (blinkState) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("NO POWER SUPPLY");
        } else {
          lcd.clear();  // Clear the display when off
        }
      }
    }
  } 

  // Read the sensor on analog A0
  int sensorReading0 = analogRead(A0);
  int range = map(sensorReading0, sensorMin, sensorMax, 0, 3);

  // Handle sensor readings
  switch (range) {
    case 0:  // A fire closer than 1.5 feet away
      Serial.println("** Close Fire **");
      break;
    case 1:  // A fire between 1-3 feet away
      Serial.println("** Distant Fire **");
      break;
    case 2:  // No fire detected
      Serial.println("No Fire");
      break;
  }

  // If fire found, turn off the master relay
  if (range == 0 || range == 1) {
    masterRelayState = false;
    Serial.println("Fire detected! Master relay OFF");
  }
}

void updateDisplay() {
  if (masterRelayState) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RM: ");
    lcd.print(relayState[0] ? "ON " : "OFF");

    lcd.setCursor(8, 0);
    lcd.print("R1: ");
    lcd.print(relayState[1] ? "ON " : "OFF");

    lcd.setCursor(0, 1);
    lcd.print("R2: ");
    lcd.print(relayState[2] ? "ON " : "OFF");

    lcd.setCursor(8, 1);
    lcd.print("R3: ");
    lcd.print(relayState[3] ? "ON " : "OFF");
  }
}
