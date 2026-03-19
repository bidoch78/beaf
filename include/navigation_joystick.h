#pragma once

#include <navigation_ctl.h>
#include <cstdint>

namespace beaf::Navigation {

    using namespace beaf::Core;

    class NavigationJoystick: public NavigationControl {
        
        private:
            uint8_t _pinX;
            uint8_t _pinY;
            uint8_t _pinSW;

        public:
            NavigationJoystick(uint8_t pinX, uint8_t pinY, uint8_t pinSW);
            NavigationJoystick(uint8_t pinX, uint8_t pinY, uint8_t pinSW, uint32_t intervalms);
            ~NavigationJoystick();

            void initialize();
            void _retrieveData();
    
    };

}