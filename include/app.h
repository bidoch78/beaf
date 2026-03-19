#pragma once

#include <navigation_ctl.h>
#include <core_parameter.h>
#include <sensor.h>
#include <map>

namespace beaf::Core {

    using namespace beaf::Sensor;
    using namespace beaf::Navigation;

    class App: public Semaphore {
        
        private:
            
            Parameters *_parameters;
            NavigationControl *_navigationCtrl;
            std::map<uint32_t, SensorItem*> _sensors;

            uint32_t _sensorRate;
            uint32_t _sensorTime;
            uint32_t _sensorCount;

            //uint32_t _lastNavDirection = NavigationControl::NavigationEvent_Nothing;

        public:
            
            App();
            ~App();

            void setParameters(Parameters *paramInstance);
            void setNavigationController(NavigationControl *navCtrl);

            void initialize();
            void addSensor(SensorItem *sensor);

            void setSensorRate(uint32_t rate);
            uint32_t getSensorRate();

            void acquire();
            void draw();

    };

}