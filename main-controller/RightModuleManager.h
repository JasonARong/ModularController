#ifndef RIGHT_MODULE_MANAGER_H
#define RIGHT_MODULE_MANAGER_H

#include "RightModuleBase.h"
#include <vector>

class RightModuleManager {
private:
    static const int RESISTOR_PIN = 2;
    std::vector<RightModuleBase*> availableModules;
    RightModuleBase* currentModule;
    BleGamepad* bleGamepad;

public:
    RightModuleManager(BleGamepad* gamepad);
    ~RightModuleManager();

    void registerModule(RightModuleBase* module);
    void setup();
    void update();
    bool isModuleConnected() const { return currentModule != nullptr; }
};

#endif
