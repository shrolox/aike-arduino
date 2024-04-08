#ifndef SPEED_SENSOR_H
#define SPEED_SENSOR_H

class SpeedSensor {
  public:
    SpeedSensor(int pin);
    
    void setup();
    void loop();
    float getTurnsPerSecond();

  private:
    int pin;
    float currentTurnsPerSecond;
    unsigned long lastTurn;
    int lastState;
    unsigned long deactivationStart;

    bool isActivated();
    bool isNewLoop();
};

class PedalSpeedSensor : public SpeedSensor {
  public:
    PedalSpeedSensor(int pin);
};

class BikeSpeedSensor : public SpeedSensor {
  public:
    BikeSpeedSensor(int pin);
};

#endif