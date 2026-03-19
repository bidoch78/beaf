#pragma once

#include <sensor.h>
#include <valueconverter.h>
#include <cstdint>

namespace beaf::Sensor {
        
    class valueConverterInterval: valueConverter<uint32_t, uint32_t> {
        
        private:
            uint32_t _iMin;
            uint32_t _iMax;
            uint32_t _oMin;
            uint32_t _oMax;

        public:
            valueConverterInterval(uint32_t oMax) {
               _iMin = 0; 
               _iMax = SensorItem::getMaxResolutionValue(SensorItem::defaultResolution);
                if (oMax < 0) { _oMin = oMax; _oMax = 0; } else { _oMin = 0; _oMax = oMax; }  
            };
            valueConverterInterval(uint32_t iMax, uint32_t oMax) {  
                if (iMax < 0) { _iMin = iMax;  _iMax = 0; } else { _iMin = 0; _iMax = iMax; }
                if (oMax < 0) { _oMin = oMax;  _oMax = 0; } else { _oMin = 0; _oMax = oMax; } 
            };
            valueConverterInterval(uint32_t iMin, uint32_t iMax, uint32_t oMin, uint32_t oMax) {  
                if (iMax < iMin) { _iMin = iMax;  _iMax = iMin; } else { _iMin = iMin; _iMax = iMax; }
                if (oMax < oMin) { _oMin = oMax;  _oMax = oMin; } else { _oMin = iMax; _oMax = oMax; }                
            };

            output convert(uint32_t value) { 

                if (value < _iMin) return _oMin;
                if (value > _iMax) return _oMax;

                return _oMin + (((float)(value-_iMin)/(float)(_iMax-_iMin)) * (float)(_oMax-_oMin));

            };
    
    };

};