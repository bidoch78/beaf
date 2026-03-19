#include <core_parameter.h> 

namespace beaf::Core {

    Parameters::Parameters() {
    };

    Parameters::~Parameters() {
        this->reset();
    };

    void Parameters::reset() {
        //for(auto const& p: _listOfParams) if (p.second) delete p.second;
        take();
        _listOfParams.clear();
        give();
    };

    void Parameters::addOrUpdateParameter(int key, Parameter param) {
        take();
        _listOfParams[key] = param;
        give();
    };

    void Parameters::removeParameter(int key) {
        //Parameter *p = this->find(key);
        //if (p) delete p;
        take();
        _listOfParams.erase(key);
        give();
    }

    Parameter Parameters::find(int key) {
        take();
        std::map<int, Parameter>::const_iterator iter=_listOfParams.find(key);
        Parameter p = (iter!=_listOfParams.end()) ? (*iter).second : std::monostate{};
        give();
        return p;
    }

    std::vector<int> Parameters::getKeys() {
        std::vector<int> keys;
        take();
        for (auto it = _listOfParams.begin(); it != _listOfParams.end(); ++it) keys.push_back(it->first);
        give();
        return keys;
    }

    void Parameters::initialize(std::map<int, Parameter> *list) {
        take();
        
        give();
    }

    bool Parameters::read() { return false; };
    bool Parameters::write() { return false; };

}