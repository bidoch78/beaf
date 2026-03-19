#include <arduino_compatibility.h>
#include <chrono>
#include <stdint.h>

#ifdef ARDUINO_COMPATIBILITY

uint32_t millis() {

    using namespace std::chrono;

    static const steady_clock::time_point start = steady_clock::now();

    return static_cast<uint32_t>(
        duration_cast<milliseconds>(
            steady_clock::now() - start
        ).count()
    );

}

#endif