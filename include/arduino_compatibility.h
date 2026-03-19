#pragma once

#ifdef ARDUINO_COMPATIBILITY

    uint32_t millis();

#else

    #include <Arduino.h>

#endif