#include <navigation_joystick.h>
#include <arduino_compatibility.h>

namespace beaf::Navigation {

    NavigationJoystick::NavigationJoystick(uint8_t pinX, uint8_t pinY, uint8_t pinSW): NavigationControl(150) { //by default 150ms interval
        _pinX = pinX;
        _pinY = pinY;
        _pinSW = pinSW;
    };

    NavigationJoystick::NavigationJoystick(uint8_t pinX, uint8_t pinY, uint8_t pinSW, uint32_t intervalms): NavigationControl(intervalms) {
        _pinX = pinX;
        _pinY = pinY;
        _pinSW = pinSW;
    };


    NavigationJoystick::~NavigationJoystick() { };

    void NavigationJoystick::initialize() {
        pinMode(_pinX, INPUT);
        pinMode(_pinY, INPUT);
        pinMode(_pinSW, INPUT_PULLUP);
    }

    void NavigationJoystick::_retrieveData() { 

        const uint16_t sensitivity = 500;

        //Read X Y & SW => 0 to 4095
        uint16_t x = analogRead(_pinX);
        uint16_t y = analogRead(_pinY);
        uint16_t sw = !digitalRead(_pinSW);

        uint16_t current = NavigationState_Nothing;

        if (x < sensitivity) {
            current += NavigationState_Left;
        }
        else if (x >= (4095-sensitivity)) {
            current += NavigationState_Right;
        }

        if (y < sensitivity) {
            current += NavigationState_Top;
        }
        else if (y >= (4095-sensitivity)) {
            current += NavigationState_Bottom;
        }

        if (sw) current += NavigationState_Validate;

        //We are in semaphore contextand this function is called inside take() / give()
        udpateState(current, false);

    };

}