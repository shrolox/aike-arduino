/*
  Aike - Arduino

  This is the main file for the Aike project, which is a smart bike project.

  Author: Pierre-Olivier Maugis @shrolox
*/

#include <Arduino.h>
#include "config.h"
#include "src/bike.h"
#include "src/button.h"

Bike bike = Bike(
  INPUT_FRONT_SPEED_SENSOR,
  INPUT_PEDAL_SPEED_SENSOR,
  OUTPUT_FRONT_LIGHT,
  OUTPUT_BACK_LIGHT
);
Button caseButton = Button(INPUT_CASE_BUTTON);


void setup() {
  // initialize bike (lights and sensors)
  bike.setup();
  caseButton.setup();

  // Start the serial communication
  Serial.begin(9600);
}

void loop() {
  if (caseButton.gotQuickPress()) {
    bike.updateLightsMode();
  }

  bike.loop();
}