#pragma once

//#include <arduino_compatibility.h>
#include <sensor.h>
#include <cstdint>
#include <variant>
#include <valueconverter_interval.h>
#include <valueconverter_voltage.h>

namespace beaf::Sensor {
        
    using namespace Sensor;

    template <class O>
    class SensorStd: public SensorItem {
        
        public:

            struct SensorStdValues {
                uint16_t analogValue;
                float voltage;
                std::variant<std::monostate, O> value;
            };

        private:
            uint8_t _pin;
            valueConverterInterval *_valueConverter;
            valueConverterVoltage *_voltageConverter;
            SensorStdValues _values;

        protected:
            void _retrieveData() { 

                _values.analogValue = analogRead(_pin);
                _values.voltage = std::get<float>(_voltageConverter->convert(_values.analogValue));
                _values.value = std::get<O>(_valueConverter->convert(_values.analogValue));
                // String a = "";
                // a += _values.analogValue;
                // a += ", ";
                // a += _values.voltage;
                // a += ", ";
                // a += std::get<O>(_values.value);
                // Serial.println(a);

            };

        public:
            SensorStd(uint32_t key, uint8_t pin, valueConverterInterval *vconv, valueConverterVoltage *voltconv): SensorItem(key), _pin(pin) { _valueConverter = vconv; _voltageConverter = voltconv; }
            SensorStd(uint32_t key, uint8_t pin, valueConverterInterval *vconv, valueConverterVoltage *voltconv, uint32_t intervalms): SensorItem(key, intervalms), _pin(pin) { _valueConverter = vconv; _voltageConverter = voltconv; };
            ~SensorStd() { delete _valueConverter; delete _voltageConverter; }

            SensorStdValues getValues() { 
                SensorStdValues v;
                if (take()) {
                    v = _values;
                }
                give();
                return v;       
            };

            void initialize() {
                pinMode(_pin, INPUT);
               _values.analogValue = 0;
               _values.voltage = 0.0;
               _values.value = std::monostate{};
            };
    
    };

};