#include "Application.h" 
#include "ConfigData.h"

#include <iostream>

namespace Engine {
    std::string_view GetConfig(){
        return kEngineConfig;
    }

    Application::Application(){

    }

    Application::~Application(){
        
    }

    void Application::Run(){
        while(true){
            
        }
    }
}