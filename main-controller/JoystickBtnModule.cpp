#include "JoystickBtnModule.h"
#include <Arduino.h>

JoystickBtnModule::JoystickBtnModule(BleGamepad* gamepad): RightModuleBase(gamepad){}

bool JoystickBtnModule::identify(int resistorValue){
    return (resistorValue >= RESISTOR_MIN && resistorValue <= RESISTOR_MAX);
}

void JoystickBtnModule::setup(){
    // Set Up 4 face buttons
    for (int i = 0; i < NUM_BUTTONS; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }

    // r1 btn and joystick
    pinMode(r1Pin, INPUT_PULLUP);
    pinMode(joystickButtonPin, INPUT_PULLUP);
    pinMode(joystickXPin, INPUT);
    pinMode(joystickYPin, INPUT);
}

void JoystickBtnModule::update(){
    // 4 face buttons
    for (int i = 0; i < NUM_BUTTONS; i++) {
        if(digitalRead(buttonPins[i]) == LOW){
            bleGamepad->press(i+1);
        } else{
            bleGamepad->release(i+1);
        }
    }

    // R1 btn
    if(digitalRead(r1Pin) == LOW){
        bleGamepad->press(R1_BUTTON);
    } else {
        bleGamepad->release(R1_BUTTON);
    }

    // Joystick
    if(digitalRead(joystickButtonPin) == LOW){
        bleGamepad->press(R3_BUTTON);
    }else {
        bleGamepad->release(R3_BUTTON);
    }

    int xValue = map(constrain(analogRead(joystickXPin), 0, JOYSTICK_X_MAX), 0, JOYSTICK_X_MAX, 32767, 0);
    int yValue = map(constrain(analogRead(joystickYPin), 0, JOYSTICK_Y_MAX), 0, JOYSTICK_Y_MAX, 0, 32767);

    bleGamepad->setRightThumb(xValue,yValue);
}

void JoystickBtnModule::cleanup() {
    // Release all buttons when disconnecting
    for (int i = 0; i < NUM_BUTTONS; i++) {
        bleGamepad->release(i + 1);
    }
    bleGamepad->release(R1_BUTTON);
    bleGamepad->release(R3_BUTTON);
    bleGamepad->setRightThumb(16383,16383);
}

const char* JoystickBtnModule::getName() {
    return "Joystick 4+1 Buttons Module";
}


