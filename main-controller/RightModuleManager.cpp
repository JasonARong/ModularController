#include "RightModuleManager.h"
#include <Arduino.h>

RightModuleManager::RightModuleManager(BleGamepad* gamepad) 
    : bleGamepad(gamepad), currentModule(nullptr) {
    pinMode(RESISTOR_PIN, INPUT);
}

RightModuleManager::~RightModuleManager() {
    for (auto module : availableModules) {
        delete module;
    }
}

void RightModuleManager::registerModule(RightModuleBase* module) {
    availableModules.push_back(module);
}

void RightModuleManager::setup() {
    // Initial module detection
    update();
}

void RightModuleManager::update() {
    int resistorValue = analogRead(RESISTOR_PIN);
    Serial.printf("Resistor value: %d\n", resistorValue);
    
    // Check if current module is still connected
    if (currentModule && !currentModule->identify(resistorValue)) {
        Serial.printf("Module %s disconnected\n", currentModule->getName());
        currentModule->cleanup();
        currentModule = nullptr;
    }
    
    // If no module is connected, check for new connections
    if (!currentModule) {
        for (auto module : availableModules) {
            if (module->identify(resistorValue)) {
                currentModule = module;
                currentModule->setup();
                Serial.printf("Module %s connected\n", currentModule->getName());
                break;
            }
        }
    }
    
    // Update current module if connected
    if (currentModule) {
        currentModule->update();
    }
}
