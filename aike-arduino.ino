/*
  Aike - Arduino

  This is the main file for the Aike project, which is a smart bike project.

  Author: Pierre-Olivier Maugis @shrolox
*/

#include <Arduino.h>
#include "config.h"
#include "src/bike.h"
#include "src/button.h"
#include "src/bluetooth_manager.h"

Bike bike = Bike(
  INPUT_FRONT_SPEED_SENSOR,
  INPUT_PEDAL_SPEED_SENSOR,
  OUTPUT_FRONT_LIGHT,
  OUTPUT_BACK_LIGHT
);
Button caseButton = Button(INPUT_CASE_BUTTON);
BluetoothManager bluetoothManager = BluetoothManager();


void setup() {
  // Start the serial communication
  Serial.begin(9600);

  // initialize bike (lights and sensors)
  bike.setup();
  caseButton.setup();
  bluetoothManager.setup();
}

void loop() {
  if (caseButton.gotQuickPress()) {
    bike.updateLightsMode();
  }

  bike.loop();
  caseButton.loop();
  Bike::BikeStatus status = bike.getStatus();
  
  Serial.println(status.speed);

  bluetoothManager.loop(status);
}