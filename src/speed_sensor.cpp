#include <Arduino.h>
#include "speed_sensor.h"

SpeedSensor::SpeedSensor(int pin) {
  this->pin = pin;
  this->deactivationStart = millis();
}

void SpeedSensor::setup() {
  pinMode(this->pin, INPUT_PULLUP);
}

void SpeedSensor::loop() {
  unsigned long now = millis();

  // Set the state varables
  if (this->isNewLoop()) {
    float turnsPerSecond = 1000.0 / (now - this->lastTurn);
    this->currentTurnsPerSecond = (this->currentTurnsPerSecond + turnsPerSecond) / 2;
    this->lastTurn = now;
  } else if (now - this->lastTurn > 1000) {
    this->currentTurnsPerSecond = 0;
  }

  if (this->isActivated() || (!this->isActivated() && this->lastState == HIGH)) {
    this->deactivationStart = now;
  }

  this->lastState = this->isActivated() ? HIGH : LOW;
}

bool SpeedSensor::isNewLoop() {
  // We consider a new loop when the sensor is activated
  // after having been deactivated for at least 100ms
  if (this->isActivated()) {
    unsigned long now = millis();
    if (this->lastState == LOW && now - this->deactivationStart > 50) {
      return true;
    }
  }
  return false;
}

bool SpeedSensor::isActivated() {
  return !digitalRead(this->pin);
}

float SpeedSensor::getTurnsPerSecond() {
  return this->currentTurnsPerSecond;
}

PedalSpeedSensor::PedalSpeedSensor(int pin) : SpeedSensor(pin) {
}

BikeSpeedSensor::BikeSpeedSensor(int pin) : SpeedSensor(pin) {
}