#include "ButtonModule.h"
#include <Arduino.h>

ButtonModule::ButtonModule(BleGamepad* gamepad) : RightModuleBase(gamepad) {}

bool ButtonModule::identify(int resistorValue) {
    return (resistorValue >= RESISTOR_MIN && resistorValue <= RESISTOR_MAX);
}

void ButtonModule::setup() {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }
}

void ButtonModule::update() {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        if (digitalRead(buttonPins[i]) == LOW) {
            bleGamepad->press(i + 1);
            Serial.printf("Button %d pressed\n", i + 1);
        } else {
            bleGamepad->release(i + 1);
        }
    }
}

void ButtonModule::cleanup() {
    // Release all buttons when disconnecting
    for (int i = 0; i < NUM_BUTTONS; i++) {
        bleGamepad->release(i + 1);
    }
}

const char* ButtonModule::getName() {
    return "4-Button Module";
}
