// Test sensor de gas tipo Butano con Arduino
// MQ-6 is a highly sensitive gas sensor to petroleum based gases but less sensitive to Alcohol and Carbon di oxide.
// https://dmohankumar.wordpress.com/2012/11/15/gas-leakage-alarm-using-mq-6-sensor-sensor-circuit-14/
// MB 07.04.2019, v1.0
// datasheet at https://www.sparkfun.com/datasheets/Sensors/Biometric/MQ-6.pdf

// MQ-6 wiring
#define analogMQ6 A0      // Signal 
#define digitalMQ6 7
//#define ledPin D7         // Device internal LED      
int MQ6sensorValue = 0;   // value read from the sensor
int MQ6digitalValue = 0;    //digital value of MQ6

// *********************************

void setup()
{
    Serial.begin(9600);
    Serial.println(F("MQ-6 Gas Sensor Flying-Fish started"));

    pinMode(analogMQ6, INPUT);
    pinMode(digitalMQ6, INPUT);

    //pinMode(ledPin, OUTPUT);
}
    
// *********************************

void loop() { 

  // A) preparation
    // turn the heater fully on
    analogWrite(analogMQ6, HIGH); // HIGH = 255
    // heat for 1 min
    delay(60000);
    // now reducing the heating power: turn the heater to approx 1,4V
    analogWrite(analogMQ6, 71.4); // 255x1400/5000
    // heat for 90 sec
    delay(90000);
    
  // B) reading    
    // CO2 via MQ7: we need to read the sensor at 5V, but must not let it heat up. So hurry!
    analogWrite(analogMQ6, HIGH); 
    delay(50); // Getting an analog read apparently takes 100uSec
    MQ6sensorValue = analogRead(analogMQ6);
    MQ6digitalValue = digitalRead(digitalMQ6);

  for (int i=0; i<10; i++) {  
  // C) print the results to the serial monitor
    Serial.print("Analogue MQ-6 PPM: ");                       
    Serial.println(MQ6sensorValue);  
    Serial.print("Digital MQ-6 PPM: ");                       
    Serial.println(MQ6digitalValue);     
  // D) interpretation
    // Detecting range: 20ppm-2000ppm carbon monoxide
    // air quality-cases: < 200 perfect, 200 - 800 normal, > 800 - 1800 high, > 1800 abnormal
  
    if (MQ6sensorValue <= 200) 
    {
        Serial.println("Air-Quality: Butano perfect");
    }
    else if ((MQ6sensorValue > 200) || (MQ6sensorValue <= 800)) // || = or
    {
        Serial.println("Air-Quality: CO normal");
    }
    else if ((MQ6sensorValue > 800) || (MQ6sensorValue <= 1800))
    {
        Serial.println("Air-Quality: CO high");
    }
    else if (MQ6sensorValue > 1800) 
    {
        //digitalWrite(ledPin, HIGH); // optical information in case of emergency
        Serial.println("Air-Quality: ALARM CO very high");
        delay(3000);
        //digitalWrite(ledPin, LOW);
    }
    else
    {
        Serial.println("MQ-6 - cant read any value - check the sensor!");
    }
delay(1000);
    }
}
