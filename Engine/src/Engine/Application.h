#pragma once

#include "Core.h"
#include "Window.h"
#include "Engine/LayerStack.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"

#include <string_view>

namespace Engine {
    ENGINE_API std::string_view GetConfig();

    class ENGINE_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();
    
        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    };

    // To be def in a CLIENT
    Application* CreateApplication();
}