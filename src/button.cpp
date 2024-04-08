#include <Arduino.h>
#include "button.h"
#include "config.h"

Button::Button(int pin) {
  this->pin = pin;
}

void Button::setup() {
    pinMode(this->pin, INPUT_PULLUP);
}

bool Button::gotQuickPress() {
    // Read the state of the button
    static int buttonState = LOW;
    int newButtonState = digitalRead(INPUT_CASE_BUTTON);
  
    // If button state has changed and the button is pressed, change the light mode
    if (newButtonState == HIGH && buttonState != newButtonState) {
        Serial.println("Button pressed");
        buttonState = newButtonState;
        return true;
    } else {
        buttonState = newButtonState;
        return false;
    }
}

bool Button::gotLongPress() {

}