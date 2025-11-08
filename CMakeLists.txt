cmake_minimum_required(VERSION 3.14)

project(magos-project VERSION 0.1 DESCRIPTION "Game Engine" LANGUAGES CXX)

set(ENGINE_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/config/engine_config.json)
file(READ ${ENGINE_CONFIG_FILE} ENGINE_CONFIG_CONTENTS)
configure_file(Engine/src/ConfigData.h.in ${CMAKE_CURRENT_BINARY_DIR}/Engine/ConfigData.h @ONLY)

add_library(Engine SHARED
    Engine/src/test.cpp
)
target_include_directories(Engine
    PUBLIC
        Engine/src
        ${CMAKE_CURRENT_BINARY_DIR}/Engine
)
target_compile_definitions(Engine
    PRIVATE ENGINE_BUILD
    PUBLIC ENGINE_DLL
)

add_executable(Sandbox
    Sandbox/src/Application.cpp
)
target_link_libraries(Sandbox PRIVATE Engine)

set_target_properties(Sandbox PROPERTIES OUTPUT_NAME "MyExit")