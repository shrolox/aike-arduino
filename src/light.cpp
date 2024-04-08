#include <Arduino.h>
#include "light.h"
#include "config.h"

Light::Light(int pin) {
    this->pin = pin;
    this->currentMode = Light::Mode::OFF;
    this->pinStatus = LOW;
}

void Light::setup() {
    pinMode(this->pin, OUTPUT);
}

void Light::loop() {
    switch (this->currentMode) {
        case OFF:
        this->pinStatus = LOW;
        break;
        case ON:
        this->pinStatus = HIGH;
        break;
        case BLINK:
        if (millis() - this->lastChangeTime > LIGHT_BLINK_INTERVAL) {
            this->lastChangeTime = millis();
            this->pinStatus = !this->pinStatus;
        }
        break;
    }
    digitalWrite(pin, this->pinStatus);
}

void Light::setMode(Light::Mode mode) {
    this->currentMode = mode;
}

Light::Mode Light::getNextMode() {
    switch (this->currentMode) {
        case OFF:
            return ON;
        case ON:
            return BLINK;
        case BLINK:
            return OFF;
    }
}

Light::Mode Light::getMode() {
    return this->currentMode;
}