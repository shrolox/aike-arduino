#ifndef BUTTON_H
#define BUTTON_H

class Button {
  public:
    Button(int pin);

    void setup();

    bool gotQuickPress();
    bool gotLongPress();

  private:
    int pin;
};

#endif