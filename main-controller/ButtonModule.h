#ifndef BUTTON_MODULE_H
#define BUTTON_MODULE_H

#include "RightModuleBase.h"

class ButtonModule : public RightModuleBase {
private:
    static const int NUM_BUTTONS = 4;
    const int buttonPins[NUM_BUTTONS] = {16, 17, 18, 19};
    
    const int RESISTOR_MIN = 400;
    const int RESISTOR_MAX = 500;

public:
    ButtonModule(BleGamepad* gamepad);
    bool identify(int resistorValue) override;
    void setup() override;
    void update() override;
    void cleanup() override;
    const char* getName() override;
};

#endif
