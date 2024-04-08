#include <Arduino.h>
#include "button.h"
#include "config.h"

Button::Button(int pin) {
  this->pin = pin;
}

void Button::setup() {
    pinMode(this->pin, INPUT_PULLUP);
}

void Button::loop() {
    this->lastState = this->currentState;
    this->currentState = !digitalRead(this->pin);

    if (this->currentState == HIGH && this->lastState == LOW) {
        this->pressStart = millis();
    }
}

bool Button::gotQuickPress() {
    if (this->currentState == LOW) {
        unsigned long pressDuration = millis() - this->pressStart;
        if (pressDuration < 400 && pressDuration > 50) {
            return true;
        }
    }
    return false;
}

bool Button::gotLongPress() {
    if (this->currentState == LOW) {
        unsigned long pressDuration = millis() - pressStart;
        if (pressDuration >= 400) {
            return true;
        }
    }
    return false;
}