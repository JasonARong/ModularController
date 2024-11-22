#ifndef RIGHT_MODULE_BASE_H
#define RIGHT_MODULE_BASE_H

#include <BleGamepad.h>

class RightModuleBase {
protected:
    BleGamepad* bleGamepad;

public:
    RightModuleBase(BleGamepad* gamepad) : bleGamepad(gamepad) {}
    virtual ~RightModuleBase() = default;
    
    // Pure virtual functions that must be implemented by derived classes
    virtual bool identify(int resistorValue) = 0;
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void cleanup() = 0;
    
    // Helper function to get module name
    virtual const char* getName() = 0;
};

#endif
