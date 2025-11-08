#pragma once

#include "Core.h"

#include <string_view>

namespace Engine {
    ENGINE_API std::string_view GetConfig();

    class ENGINE_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    // To be def in a CLIENT
    Application* CreateApplication();
}