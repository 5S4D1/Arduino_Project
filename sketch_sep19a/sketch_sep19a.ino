#include "arduino_secrets.h"
#include "thingProperties.h"

const int rpin_1 = 3;

const int threshold = 80;

Schedule schedValues = plant_schedule_1.getValue();

void setup() {


  //declare relay pins
  pinMode(rpin_1, OUTPUT);

  delay(1500);

  initProperties();
}

void loop() {
  ArduinoCloud.update();
  sensor_1 = sensorReading(A1);
  
  onPlantSchedule1Change();

}

int sensorReading(int pin){
  int result;
  int reading = analogRead(pin);
  result = map(reading, 0, 1023, 100, 0);
  return result;
}

void onPlantSchedule1Change() {
  if (automatic_mode) {
    if (sensor_1 < threshold && plant_schedule_1.isActive()) {
      digitalWrite(rpin_1, HIGH);
    } else {
      digitalWrite(rpin_1, LOW);
    }
  }
}




void onRelay1Change() {
  if (relay_1) {
    digitalWrite(rpin_1, HIGH);
  } else {
    digitalWrite(rpin_1, LOW);
  }
}


void onAutomaticModeChange() {
}
