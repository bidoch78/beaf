#pragma once

#include <cstdint>
#include <variant>

namespace beaf::Sensor {
        
    template <class I, class O>
    class valueConverter {
        
        public:
            using output = std::variant<std::monostate, O>;

        public:
            virtual output convert(I input) { return std::monostate{}; };
    
    };

};