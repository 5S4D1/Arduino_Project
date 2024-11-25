#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // Include the I2C LCD library
#include <DHT.h>                // Include the DHT library

// DHT11 Sensor setup
#define DHTPIN 2         // Pin where DHT11 is connected
#define DHTTYPE DHT11    // Define the sensor type
DHT dht(DHTPIN, DHTTYPE);

// Capacitive Soil Moisture Sensor setup
#define SOIL_MOISTURE_PIN A0 // Analog pin for soil moisture sensor

// UV Sensor (GUVA-S12SD) setup
#define UV_SENSOR_PIN A1      // Analog pin for UV sensor (GUVA-S12SD)

// Initialize the LCD, I2C address 0x27 might vary based on your display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Function to determine soil condition based on moisture percentage
String getSoilCondition(int moisturePercent) {
  if (moisturePercent <= 30) {
    return "Dry";
  } else if (moisturePercent <= 60) {
    return "Good";
  } else {
    return "Wet";
  }
}

void setup() {
  // Initialize the DHT11 sensor
  dht.begin();

  // Initialize the LCD and turn on the backlight
  lcd.begin(16,2);
  lcd.backlight();

  // Show welcome message
  lcd.setCursor(0, 0);           // Set cursor to first row, first column
  lcd.print("   Welcome to ");   // Display "Welcome to"
  lcd.setCursor(0, 1);           // Set cursor to second row, first column
  lcd.print("    SynapseX ");    // Display "SynapseX Sys"
  delay(1000);                   // Delay for 1 second
  lcd.clear();                   // Clear the screen

  lcd.setCursor(0, 0);           // Set cursor to first row
  lcd.print("   Monitoring");    // Display "Monitoring"
  lcd.setCursor(0, 1);           // Set cursor to second row
  lcd.print("     System");      // Display "System"
  delay(2000);                   // Delay for 2 seconds
  lcd.clear();                   // Clear the screen again after the welcome message

  // Start Serial for debugging
  Serial.begin(9600);
  Serial.println("Setup Complete");
}

void loop() {
  Serial.println("Reading Sensors...");

  // Read DHT11 data
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Read soil moisture sensor
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  int soilMoisturePercent = map(soilMoistureValue, 0, 1023, 0, 100); // Convert to percentage

  // Determine soil condition
  String soilCondition = getSoilCondition(soilMoisturePercent);

  // Read UV sensor (GUVA-S12SD)
  int uvRaw = analogRead(UV_SENSOR_PIN);
  float uvVoltage = (uvRaw / 1023.0) * 5.0;  // Assuming 5V reference, calculate voltage
  float uvIntensity = uvVoltage * 307;       // UV intensity in mW/m² (based on sensor datasheet)

  // Display temperature and humidity on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1); // Display one decimal place
  lcd.print("C ");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity, 1); // Display one decimal place
  lcd.print("%");
  delay(2000); // Display the data for 2 seconds

  // Display soil moisture and condition on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(soilMoisturePercent);
  lcd.print("% ");
  
  lcd.setCursor(0, 1);
  lcd.print("Condition: ");
  lcd.print(soilCondition);
  lcd.print("   "); // Extra spaces to clear any residual characters
  delay(2000); // Display the soil moisture and condition for 2 seconds

  // Display UV intensity on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("UV Int: ");
  lcd.print(uvIntensity,1); // Display one decimal place
  lcd.setCursor(0, 1);
  lcd.print("mW/m^2");

  // Optionally, display additional information or clear the line
  lcd.setCursor(0, 1);
  lcd.print("               "); // Clear second line
  delay(2000); // Display the UV intensity for 2 seconds

  // Print data to the Serial Monitor for debugging
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Soil Moisture: ");
  Serial.print(soilMoisturePercent);
  Serial.println(" %");

  Serial.print("Soil Condition: ");
  Serial.println(soilCondition);

  Serial.print("UV Intensity: ");
  Serial.print(uvIntensity);
  Serial.println(" mW/m²");

  delay(1000); // Short delay before the next loop iteration
}
