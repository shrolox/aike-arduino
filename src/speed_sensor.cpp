#include <Arduino.h>
#include "speed_sensor.h"

SpeedSensor::SpeedSensor(int pin) {
  this->pin = pin;
}

void SpeedSensor::setup() {
  pinMode(this->pin, INPUT_PULLUP);
}

bool SpeedSensor::isActivated() {
  return !digitalRead(this->pin);
}

PedalSpeedSensor::PedalSpeedSensor(int pin) : SpeedSensor(pin) {
}

BikeSpeedSensor::BikeSpeedSensor(int pin) : SpeedSensor(pin) {
}