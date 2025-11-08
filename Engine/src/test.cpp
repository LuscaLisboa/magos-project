#include "test.h" 
#include "ConfigData.h"

#include <iostream>

namespace Engine {
    void Print(){
        std::cout << "Hello World!\n";
    }

    std::string_view GetConfig(){
        return kEngineConfig;
    }
}