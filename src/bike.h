#include "config.h"
#include "light.h"
#include "speed_sensor.h"

#ifndef BIKE_H
#define BIKE_H

#define WHEEL_CIRCUMFERENCE 2.07

class Bike {
  public:
    Bike(int frontSpeedSensorPin, int pedalSpeedSensorPin, int frontLightPin, int backLightPin);

    struct BikeStatus {
      float speed;
      float pedalSpeed;
      int gear;
      Light::Mode frontLightMode;
      Light::Mode backLightMode;
    };

    BikeStatus getStatus();
    void setup();
    void loop();
    void updateLightsMode();

  private:
    BikeSpeedSensor *frontSpeedSensor;
    PedalSpeedSensor *pedalSpeedSensor;
    Light *frontLight;
    Light *backLight;

    float getPedalTurnsPerSecond();
    float getWheelTurnsPerSecond();
    float getBikeKmPerHour();
};

#endif