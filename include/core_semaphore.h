#pragma once

namespace beaf::Core {

    class Semaphore {

        private:

#ifdef ACTIVATE_MUTEX
            static uint32_t portDelay;
            SemaphoreHandle_t _mutex;
#endif

        protected:
            bool take();
            void give();

        public:
            Semaphore();
            ~Semaphore();
    
    };

}