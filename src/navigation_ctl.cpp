#include <navigation_ctl.h>
#include <arduino_compatibility.h>

namespace beaf::Navigation {
        
    NavigationControl::NavigationControl() : SensorItem(0) {};
    NavigationControl::NavigationControl(uint32_t intervalms) : SensorItem(0, intervalms) {};
    NavigationControl::~NavigationControl() {};

    NavigationControl::navigationState NavigationControl::getState() {
        navigationState dir;
        if (take()) dir = _currentState;
        give();
        return dir;
    };

    void NavigationControl::setState(NavigationControl::navigationState s) {
        if (take()) _currentState = s;
        give();
    };

    void NavigationControl::resetEvent() {
        if (take()) _currentState.event = 0;
        give();
    }

    void NavigationControl::udpateState(uint16_t c, bool bypassSemaphore) {
        if (bypassSemaphore || take()) {
            if (c != _currentState.current) {
                _currentState.current = c;
                _currentState.event = c;
            }
        }
        if (!bypassSemaphore) give();
    };

}