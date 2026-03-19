#pragma once

#include <core_semaphore.h>
#include <variant>
#include <iostream>
#include <vector>
#include <map>
#include <optional>

namespace beaf::Core {

    using Parameter = std::variant<std::monostate, int, float, std::string>;

    class Parameters: private Semaphore {

        private:
            std::map<int, Parameter> _listOfParams;
        
        protected:

            void initialize(std::map<int, Parameter> *list);

        public:
            Parameters();
            ~Parameters();

            void reset();
            
            void addOrUpdateParameter(int key, Parameter param);
            void removeParameter(int key);
            Parameter find(int key);

            virtual bool read();
            virtual bool write();

            std::vector<int> getKeys();

    };

}