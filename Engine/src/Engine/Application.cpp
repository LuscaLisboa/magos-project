#include "Application.h" 
#include "ConfigData.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Log.h"

namespace Engine {
    std::string_view GetConfig(){
        return kEngineConfig;
    }

    Application::Application(){

    }

    Application::~Application(){
        
    }

    void Application::Run(){
        WindowResizeEvent e(1200, 720);
        ENGINE_TRACE(e);

        while(true);
    }
}