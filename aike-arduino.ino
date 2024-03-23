/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

#define OUTPUT_FRONT_LIGHT 26 // A0 blue
#define OUTPUT_BACK_LIGHT 25 // A1 green
#define INPUT_FRONT_SPEED_SENSOR 14 // 14 grey
#define INPUT_PEDAL_SPEED_SENSOR 32 // 32 white
#define INPUT_CASE_BUTTON 15 // 15 purple

#define LIGHT_BLINK_INTERVAL 100 // milliseconds

enum LightMode {
  OFF,
  ON,
  BLINK
};

struct LightStatus {
  LightMode mode;
  unsigned long lastChangeTime;
  int pinStatus;
};

LightStatus frontLightStatus = {OFF, 0};
LightStatus backLightStatus = {OFF, 0};

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(OUTPUT_FRONT_LIGHT, OUTPUT);
  pinMode(OUTPUT_BACK_LIGHT, OUTPUT);
  pinMode(INPUT_FRONT_SPEED_SENSOR, INPUT_PULLUP);
  pinMode(INPUT_PEDAL_SPEED_SENSOR, INPUT_PULLUP);
  pinMode(INPUT_CASE_BUTTON, INPUT_PULLUP);

  // Start the serial communication
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  // Read the state of the button on the case, and update the lights mode accodingly
  bool buttonPressed = readCaseButton();
  bool speedSensorActivated = readSpeedSensor();
  bool pedalSpeedSensorActivated = readPedalSpeedSensor();

  if (pedalSpeedSensorActivated) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  if (buttonPressed) {
    updateLightMode(&frontLightStatus);
    updateLightMode(&backLightStatus);
  }

  // update lights
  loopLight(&frontLightStatus, OUTPUT_FRONT_LIGHT);
  loopLight(&backLightStatus, OUTPUT_BACK_LIGHT);
}

void updateLightMode(LightStatus *status) {
  LightMode nextLightMode = getNextLightMode(&frontLightStatus);
  
  if (status->mode != nextLightMode) {
    status->mode = nextLightMode;
    status->lastChangeTime = millis();
  }
}

bool readCaseButton() {
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

bool readSpeedSensor() {
  // Read the state of the button
  // static int sensorState = LOW;
  // int newSensorState = digitalRead(INPUT_FRONT_SPEED_SENSOR);
  
  // // If button state has changed and the button is pressed, change the light mode
  // if (newSensorState == HIGH && sensorState != newSensorState) {
  //   sensorState = newSensorState;
  //   return true;
  // } else {
  //   sensorState = newSensorState;
  //   return false;
  //}
  return !digitalRead(INPUT_FRONT_SPEED_SENSOR);
}

bool readPedalSpeedSensor() {
  // Read the state of the button
  // static int sensorState = LOW;
  // int newSensorState = digitalRead(INPUT_PEDAL_SPEED_SENSOR);
  
  // // If button state has changed and the button is pressed, change the light mode
  // if (newSensorState == HIGH && sensorState != newSensorState) {
  //   sensorState = newSensorState;
  //   return true;
  // } else {
  //   sensorState = newSensorState;
  //   return false;
  // }
  return !digitalRead(INPUT_PEDAL_SPEED_SENSOR);
}

LightMode getNextLightMode(LightStatus *status) {
  switch (status->mode) {
    case OFF:
      return ON;
    case ON:
      return BLINK;
    case BLINK:
      return OFF;
  }
}

void loopLight(LightStatus *status, int pin) {
  switch (status->mode) {
    case OFF:
      digitalWrite(pin, LOW);
      status->pinStatus = LOW;
      break;
    case ON:
      digitalWrite(pin, HIGH);
      status->pinStatus = HIGH;
      break;
    case BLINK:
      if (millis() - status->lastChangeTime > LIGHT_BLINK_INTERVAL) {
        status->lastChangeTime = millis();
        status->pinStatus = !status->pinStatus;
        digitalWrite(pin, status->pinStatus);
      }
      break;
  }
}
