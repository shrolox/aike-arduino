#include "config.h"
#include "bike.h"
#include "light.h"
#include "speed_sensor.h"

Bike::Bike(int frontSpeedSensorPin, int pedalSpeedSensorPin, int frontLightPin, int backLightPin) {
    this->frontSpeedSensor = new BikeSpeedSensor(frontSpeedSensorPin);
    this->pedalSpeedSensor = new PedalSpeedSensor(pedalSpeedSensorPin);
    this->frontLight = new Light(frontLightPin);
    this->backLight = new Light(backLightPin);
}

void Bike::setup() {
    this->frontSpeedSensor->setup();
    this->pedalSpeedSensor->setup();
    this->frontLight->setup();
    this->backLight->setup();
}

void Bike::loop() {
    this->frontLight->loop();
    this->backLight->loop();
}

Bike::BikeStatus Bike::getStatus() {
    BikeStatus status;
    status.speed = getBikeKmPerHour();
    status.pedalSpeed = getPedalTurnsPerSecond() * 60;
    status.gear = 0;
    status.frontLightMode = this->frontLight->getMode();
    status.backLightMode = this->backLight->getMode();
    return status;
}

void Bike::updateLightsMode() {
    Light::Mode nextMode = this->frontLight->getNextMode();

    this->frontLight->setMode(nextMode);
    this->backLight->setMode(nextMode);
}

float Bike::getPedalTurnsPerSecond() {
    return 0;
}

float Bike::getWheelTurnsPerSecond() {
    return 0;
}

float Bike::getBikeKmPerHour() {
    return 0;
}