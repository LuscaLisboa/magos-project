#include "Application.h" 
#include "ConfigData.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Log.h"

namespace Engine {
    std::string_view GetConfig(){
        return kEngineConfig;
    }

    Application::Application(){
        m_Window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application(){
        
    }

    void Application::Run(){
        while(m_Running) {
            m_Window->OnUpdate();
        }
    }
}