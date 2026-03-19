#include <FreeRTOS.h>
#include <semphr.h>
#include <core_semaphore.h> 

namespace beaf::Core {

    #ifdef ACTIVATE_MUTEX
        uint32_t Semaphore::portDelay = portMAX_DELAY; //(10000 * portTICK_PERIOD_MS)
    #endif

    Semaphore::Semaphore() {

        #ifdef ACTIVATE_MUTEX
            _mutex = xSemaphoreCreateMutex();
        #endif

    }

    Semaphore::~Semaphore() {

        #ifdef ACTIVATE_MUTEX
            if (_mutex) vSemaphoreDelete(_mutex);
        #endif

    }

    bool Semaphore::take() {

        #ifdef ACTIVATE_MUTEX
            return xSemaphoreTake(xSemaphore, Semaphore::portDelay) == pdTRUE;
        #else
            return true;
        #endif

    }

    void Semaphore::give() {

        #ifdef ACTIVATE_MUTEX
            xSemaphoreGive(mutex);
        #endif

    }

}