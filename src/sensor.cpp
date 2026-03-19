#include <arduino_compatibility.h>
#include <core_semaphore.h>
#include <sensor.h>
#include <cstdint>

namespace beaf::Sensor {

    using namespace beaf::Core;

    SensorItem::SensorItem(uint32_t key) { 
        _intervalms = 0;
        _resolution = SensorItem::defaultResolution; 
    };

    SensorItem::SensorItem(uint32_t key, uint32_t intervalms): _intervalms(intervalms) { 
        _resolution = SensorItem::defaultResolution; 
    };

    uint32_t SensorItem::getKey() { return _key; }

    bool SensorItem::read() { 

        uint32_t now = millis();

        if (_intervalms) {
            if (!((now - _lastReadms) >= _intervalms)) return false;
        }

        _lastReadms = now;
        if (take()) _retrieveData();
        give();
        
        return true;

    };

    uint8_t SensorItem::defaultResolution = 12;

    uint32_t SensorItem::getMaxResolutionValue(uint8_t nbits) {
        return (nbits > 32) ? UINT32_MAX : ((1ULL << nbits) - 1);
    } 

}