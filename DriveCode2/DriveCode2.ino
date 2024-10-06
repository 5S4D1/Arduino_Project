// Define pin connections
const int mq9Pin = A0;  // MQ-9 sensor connected to Analog pin A0
const int mq135Pin = A1; // MQ-135 sensor connected to Analog pin A1

// Set thresholds for the sensors (These are just examples; calibrate as needed)
const float mq9Threshold = 410;  // Set threshold for MQ-9
const float mq135Threshold = 100; // Set threshold for MQ-135

// set relay
const float relay = 7;  // Set relay pin

void setup() {
  // setup pinMode
  pinMode(relay, OUTPUT);
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
}

void loop() {
  // Read analog values from the sensors
  int mq9Value = analogRead(mq9Pin);   // Reading the value from MQ-9
  int mq135Value = analogRead(mq135Pin); // Reading the value from MQ-135

  // Print sensor values to the serial monitor
  Serial.print("MQ-9 Sensor Value: ");
  Serial.println(mq9Value);
  Serial.print("MQ-135 Sensor Value: ");
  Serial.println(mq135Value);
  
  // Check if the MQ-9 sensor value exceeds the threshold
  if (mq9Value > mq9Threshold) {
    Serial.println("MQ-9: High levels of CO or CH4 detected!");
    digitalWrite(relay, HIGH);
  } else {
    Serial.println("MQ-9: Normal CO/CH4 levels.");
    digitalWrite(relay, LOW);
  }

  // Check if the MQ-135 sensor value exceeds the threshold
  if (mq135Value > mq135Threshold) {
    Serial.println("MQ-135: Poor air quality detected!");
    digitalWrite(relay, HIGH);
  } else {
    Serial.println("MQ-135: Air quality is good.");
    digitalWrite(relay, LOW);
  }

  // Wait for a second before taking new readings
  delay(1000);
}
