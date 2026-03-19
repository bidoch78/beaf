#pragma once

#include <core_semaphore.h>
#include <cstdint>

namespace beaf::Sensor {
        
    using namespace Core;

    class SensorItem: public Semaphore {
        
        private:
            uint32_t _key;
            uint32_t _intervalms;
            uint32_t _lastReadms;
            uint8_t _resolution;

        protected:
            virtual void _retrieveData() { };

        public:
            SensorItem(uint32_t key);
            SensorItem(uint32_t key, uint32_t intervalms);

            uint32_t getKey();

            virtual void initialize() { };
            virtual float getVoltage() { return 0.0; };
            bool read(); //return yes if get value otherwise return false (because interval)

            static uint8_t defaultResolution;

            static uint32_t getMaxResolutionValue(uint8_t nbits);

    };

};