#ifndef SPEED_SENSOR_H
#define SPEED_SENSOR_H

class SpeedSensor {
  public:
    SpeedSensor(int pin);
    
    void setup();
    bool isActivated();

  private:
    int pin;
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