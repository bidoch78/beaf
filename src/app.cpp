#include <app.h>
#include <arduino_compatibility.h>

namespace beaf::Core {

    App::App() : Semaphore() {
        _sensorRate = 0;
        _sensorTime = 0;
        _sensorCount = 0;
    };

    App::~App() {
        delete _parameters;
    };

    void App::setParameters(Parameters *paramInstance) { 
        _parameters = paramInstance;
    };

    void App::setNavigationController(NavigationControl *navCtrl) {
        _navigationCtrl = navCtrl;
    };

    void App::addSensor(SensorItem *sensor) {
        _sensors[sensor->getKey()] = sensor;
    };

    void App::initialize() {

        //Acquire Sensors
        for (auto sensor = _sensors.begin(); sensor != _sensors.end(); ++sensor) sensor->second->initialize();

        //Check navigation controller
        if (_navigationCtrl) _navigationCtrl->initialize();

    };

    void App::setSensorRate(uint32_t rate) {
        if (take()) {
            _sensorRate = rate;
        } 
        give();
    }

    uint32_t App::getSensorRate() {
        uint32_t rate = 0;
        if (take()) rate = _sensorRate;
        give();
        return rate;
    }

    void App::acquire() {

        //Acquire Sensors
        for (auto sensor = _sensors.begin(); sensor != _sensors.end(); ++sensor) {
            if (sensor->second->read()) _sensorCount++;
        }

        uint32_t currentMS = millis();
        if ((currentMS - _sensorTime) > 1000) {
            _sensorTime = currentMS;
            _sensorRate = _sensorCount;
            _sensorCount = 0;
        } 

        //Check navigation controller
        if (_navigationCtrl) {
            
            _navigationCtrl->read();
            NavigationControl::navigationState navStateS = _navigationCtrl->getState();
            NavigationControl::navigationReadableState rState(navStateS.event);

            if (rState.value) {

                String a = "Dir: ";
                a += rState.value;

                if (rState.left) a += " Left ";
                if (rState.right) a += " Right ";
                if (rState.top) a += " Top ";
                if (rState.bottom) a += " Bottom ";

                a += String(rState.horizontal) + String(rState.vertical);
                Serial.println(a);
                
            }

            _navigationCtrl->resetEvent();

        }
        
    }

    void App::draw() {

    }

}