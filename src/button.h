#ifndef BUTTON_H
#define BUTTON_H

class Button {
  public:
    Button(int pin);

    void setup();
    void loop();

    bool gotQuickPress();
    bool gotLongPress();

  private:
    int pin;
    int lastState;
    int currentState;
    unsigned long pressStart;
};

#endif