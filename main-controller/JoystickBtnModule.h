#ifndef JOYSTICK_BTN_MODULE_H
#define JOYSTICK_BTN_MODULE_H

#include "RightModuleBase.h"

class JoystickBtnModule : public RightModuleBase {
    private:
        static const int NUM_BUTTONS = 4;
        const int buttonPins[NUM_BUTTONS] = {16, 17, 18, 19};
        // Physical Pins
        const int r1Pin = 5;
        const int joystickButtonPin = 15;
        const int joystickXPin = 26;
        const int joystickYPin = 27;
        const int JOYSTICK_X_MAX = 3720;
        const int JOYSTICK_Y_MAX = 3720;
        // Virtual Buttons
        const int R1_BUTTON = 8;
        const int R3_BUTTON = 15;

        const int RESISTOR_MIN = 600;
        const int RESISTOR_MAX = 700;
    public:
        JoystickBtnModule(BleGamepad* gamepad);
        bool identify(int resistorValue) override;
        void setup() override;
        void update() override;
        void cleanup() override;
        const char* getName() override;
    };

#endif