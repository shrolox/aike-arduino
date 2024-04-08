#ifndef LIGHT_H
#define LIGHT_H

class Light {
  public:
    enum Mode {
      OFF,
      ON,
      BLINK
    };

    Light(int pin);
    
    void setup();
    void loop();

    void setMode(Light::Mode mode);
    
    Light::Mode getNextMode();
    Light::Mode getMode();
  
  private:
    int pin;
    unsigned long lastChangeTime;
    Light::Mode currentMode;
    int pinStatus;
};

#endif