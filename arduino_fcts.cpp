#include <config.h>
#include <arduino_fcts.h>
#include <chrono>
#include <stdint.h>

#ifdef ADD_ARDUINO_FCTS

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