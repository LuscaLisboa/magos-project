cmake_minimum_required(VERSION 3.14)

project(magos-project VERSION 0.1.0 DESCRIPTION "Game Engine" LANGUAGES C CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Engine config
set(ENGINE_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/config/engine_config.json)
file(READ ${ENGINE_CONFIG_FILE} ENGINE_CONFIG_CONTENTS)
configure_file(Engine/src/ConfigData.h.in ${CMAKE_CURRENT_BINARY_DIR}/Engine/ConfigData.h @ONLY)

# GLFW subproject
add_subdirectory(Engine/vendor/GLFW)

# glad own lib
add_library(glad STATIC Engine/vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC Engine/vendor/glad/include)

# OpenGL
find_package(OpenGL REQUIRED)

# Engine DLL
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Engine/vendor/ImGui)
add_library(Engine SHARED
    Engine/src/Engine/Application.cpp
    Engine/src/Engine/Log.cpp
    Engine/src/Engine/Layer.cpp
    Engine/src/Engine/LayerStack.cpp
    Engine/src/Engine/ImGui/ImGuiLayer.cpp
    Engine/src/Platform/Windows/WindowsWindow.cpp
    Engine/src/enginepch.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Engine includes exposure
target_include_directories(Engine
    PUBLIC
        Engine/src
        ${CMAKE_CURRENT_BINARY_DIR}/Engine
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/vendor/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/vendor/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/vendor/GLFW/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/vendor/ImGui
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/vendor/ImGui/backends
)

# PCH
target_precompile_headers(Engine 
    PRIVATE
        Engine/src/enginepch.h
)

# export/import defines
target_compile_definitions(Engine
    PRIVATE ENGINE_BUILD IMGUI_IMPL_OPENGL_LOADER_GLAD
    PUBLIC ENGINE_DLL
)

# Engine internal dependencies
target_link_libraries(Engine
    PRIVATE
        glfw
        glad
        OpenGL::GL
)

# Sandbox .exe
add_executable(Sandbox
    Sandbox/src/SandboxApp.cpp
)
target_link_libraries(Sandbox 
    PRIVATE 
        Engine
)

set_target_properties(Sandbox PROPERTIES OUTPUT_NAME "MyExit")