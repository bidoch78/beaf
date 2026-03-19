#pragma once

#include <optional>

namespace beaf::Core {
        
    template <class T>
    class ChangeValue {
        
        private:
            std::optional<T> _lastChangeValue;
            std::optional<T> _current;

        public:
        
            bool hasChanged(T value) {
                _current = value;
                if (!_lastChangeValue.has_value() || _lastChangeValue != value) {
                    _lastChangeValue = value;
                    return true;
                }
                return false;
            }

            bool hasChanged(T value, T sensibiity) {
                _current = value;
                if (!_lastChangeValue.has_value()) {  _lastChangeValue = value; return true; }

                T min = value - sensibiity;
                T max = value + sensibiity;
                if (_lastChangeValue < min || _lastChangeValue > max) {  _lastChangeValue = value; return true; }

                return false;
            }

            bool hasValue() {
                return _current.has_value();
            }

            T getValue(T defaultValue) {
                return _current.has_value() ? _current.value() : defaultValue;
            }

            void reset() {
                _lastChangeValue.reset();
                _current.reset();
            }

    };

}