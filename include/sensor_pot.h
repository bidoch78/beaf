#pragma once

#include <sensor_std.h>
#include <cstdint>

namespace beaf::Sensor {
        
    using namespace Sensor;

    class SensorPot: public SensorStd<uint32_t> {
        
        public:
            SensorPot(uint32_t key, uint8_t pin, valueConverterInterval *vconv, valueConverterVoltage *voltconv) : SensorStd<uint32_t>(key, pin, vconv, voltconv) { }
            SensorPot(uint32_t key, uint8_t pin, valueConverterInterval *vconv, valueConverterVoltage *voltconv, uint32_t intervalms): SensorStd<uint32_t>(key, pin, vconv, voltconv, intervalms) { }

    };

};