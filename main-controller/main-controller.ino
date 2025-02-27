#include <Arduino.h>
#include <BleGamepad.h>
#include "RightModuleManager.h"
#include "ButtonModule.h"
#include "JoystickBtnModule.h"

BleGamepad bleGamepad;
BleGamepadConfiguration bleGamepadConfig;
RightModuleManager* rightModuleManager;

// Left Part
const int dpadPins[] = {23, 12, 13, 22}; // Up, Down, Left, Right
int dpadState = DPAD_CENTERED;
const int joystickButtonPin = 14;
const int joystickXPin = 34;
const int joystickYPin = 39;
const int JOYSTICK_X_MAX = 3720;
const int JOYSTICK_Y_MAX = 3720;

const int L3_BUTTON = 14;

void setup() {
    Serial.begin(115200);
    
    // Left Part Setup
    for (int i = 0; i < 4; i++) {
        pinMode(dpadPins[i], INPUT_PULLUP);
    }
    pinMode(joystickButtonPin, INPUT_PULLUP);
    pinMode(joystickXPin, INPUT);
    pinMode(joystickYPin, INPUT);

    // BleGamepad Setup
    bleGamepadConfig.setAxesMin(0x0000);
    bleGamepadConfig.setAxesMax(0x7FFF);
    bleGamepad.begin(&bleGamepadConfig);

    // Right Part Setup
    rightModuleManager = new RightModuleManager(&bleGamepad);
    rightModuleManager->registerModule(new ButtonModule(&bleGamepad));
    rightModuleManager->registerModule(new JoystickBtnModule(&bleGamepad));
    rightModuleManager->setup();
}

void updateLeftPart() {
    // D-pad logic
    bool up = digitalRead(dpadPins[0]) == LOW;
    bool down = digitalRead(dpadPins[1]) == LOW;
    bool left = digitalRead(dpadPins[2]) == LOW;
    bool right = digitalRead(dpadPins[3]) == LOW;

    if (up && right) dpadState = DPAD_UP_RIGHT;
    else if (up && left) dpadState = DPAD_UP_LEFT;
    else if (down && right) dpadState = DPAD_DOWN_RIGHT;
    else if (down && left) dpadState = DPAD_DOWN_LEFT;
    else if (up) dpadState = DPAD_UP;
    else if (down) dpadState = DPAD_DOWN;
    else if (left) dpadState = DPAD_LEFT;
    else if (right) dpadState = DPAD_RIGHT;
    else dpadState = DPAD_CENTERED;

    bleGamepad.setHat(dpadState);

    // Joystick logic
    if (digitalRead(joystickButtonPin) == LOW) {
        bleGamepad.press(L3_BUTTON);
        //bleGamepad.setAxes(0, 0);
    } else {
        bleGamepad.release(L3_BUTTON);
    }

    int xValue = map(constrain(analogRead(joystickXPin), 0, JOYSTICK_X_MAX), 0, JOYSTICK_X_MAX, 32767, 0);
    int yValue = map(constrain(analogRead(joystickYPin), 0, JOYSTICK_Y_MAX), 0, JOYSTICK_Y_MAX, 32767, 0);
    bleGamepad.setLeftThumb(xValue, yValue);
}

void loop() {
    if (bleGamepad.isConnected()) {
        rightModuleManager->update();
        updateLeftPart();
        bleGamepad.sendReport();
        delay(100);
    }
}
