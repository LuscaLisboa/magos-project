#pragma once

#include <string_view>

#if defined(_WIN32) && defined(ENGINE_DLL)
    #if defined(ENGINE_BUILD)
        #define ENGINE_API __declspec(dllexport)
    #else
        #define ENGINE_API __declspec(dllimport)
    #endif
#else
    #define ENGINE_API
#endif

namespace Engine {
    ENGINE_API void Print();
    ENGINE_API std::string_view GetConfig();
}