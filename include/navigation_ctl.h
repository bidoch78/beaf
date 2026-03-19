#pragma once

#include <sensor.h>
#include <cstdint>

namespace beaf::Navigation {

    using namespace beaf::Sensor;

    class NavigationControl: public SensorItem {
        
        public:

            static const uint16_t NavigationState_Nothing = 0;
            static const uint16_t NavigationState_Top = 1;
            static const uint16_t NavigationState_Bottom = 2;
            static const uint16_t NavigationState_Left = 4;
            static const uint16_t NavigationState_Right = 8;
            static const uint16_t NavigationState_Validate = 16;

            struct navigationState {
                uint16_t current;
                uint16_t event;
            };

            struct navigationReadableState {
                uint16_t value;
                bool left;
                bool right;
                bool top;
                bool bottom;
                bool click;
                char vertical;
                char horizontal;
                navigationReadableState(uint16_t v) {

                    left = false;
                    right = false;
                    top = false;
                    bottom = false;
                    click = false;
                    vertical = 0;
                    horizontal = 0;

                    value = v;

                    if (v) {

                        if ((v & NavigationControl::NavigationState_Left) == NavigationControl::NavigationState_Left) {
                            left = true;
                            horizontal = 'L';
                        }
                        if ((v & NavigationControl::NavigationState_Right) == NavigationControl::NavigationState_Right) {
                            right = true;
                            horizontal = 'R';
                        }
                        if ((v & NavigationControl::NavigationState_Top) == NavigationControl::NavigationState_Top) {
                            top = true;
                            vertical = 'T';
                        }
                        if ((v & NavigationControl::NavigationState_Bottom) == NavigationControl::NavigationState_Bottom) {
                            bottom = true;
                            vertical = 'B';
                        }
                        if ((v & NavigationControl::NavigationState_Validate) == NavigationControl::NavigationState_Validate) {
                            click = true;
                        }

                    }
 
                }
            };  

        private:
            navigationState _currentState;
            
        public:

            NavigationControl();
            NavigationControl(uint32_t intervalms);
            ~NavigationControl();

            navigationState getState();
            void setState(navigationState s);
            void udpateState(uint16_t c, bool bypassSemaphore = false);
            void resetEvent();

            virtual void initialize() { };

    };

}