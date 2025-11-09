#pragma once

#include "Core.h"
#include "Window.h"

#include <string_view>

namespace Engine {
    ENGINE_API std::string_view GetConfig();

    class ENGINE_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();
    
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // To be def in a CLIENT
    Application* CreateApplication();
}