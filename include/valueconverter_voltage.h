#pragma once

#include <sensor.h>
#include <valueconverter.h>
#include <cstdint>
#include <arduino_compatibility.h>

namespace beaf::Sensor {
        
    class valueConverterVoltage: valueConverter<uint32_t, float> {
        
        private:
            uint32_t _iMin;
            uint32_t _iMax;
            float _oMin;
            float _oMax;

        public:
            valueConverterVoltage(float oMax) {
               _iMin = 0; 
               _iMax = SensorItem::getMaxResolutionValue(SensorItem::defaultResolution);
                if (oMax < 0) { _oMin = oMax;  _oMax = 0; } else { _oMin = 0; _oMax = oMax; }  
            };
       
            output convert(uint32_t value) { 

                if (value < _iMin) return _oMin;
                if (value > _iMax) return _oMax;

                return _oMin + (((float)(value-_iMin)/(float)(_iMax-_iMin)) * (float)(_oMax-_oMin));

            };
    
    };

};