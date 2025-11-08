#pragma once

#if defined(_WIN32)

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv){

    Engine::Log::Init();
    ENGINE_CORE_WARN("Core Log Initialized");
    ENGINE_INFO("Client Log Initialized");

    auto app = Engine::CreateApplication();
    app->Run();
    delete app;
}

#endif