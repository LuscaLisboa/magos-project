#pragma once


#if defined(_WIN32)
    #if defined(ENGINE_BUILD)
        #define ENGINE_API __declspec(dllexport)
    #else
        #define ENGINE_API __declspec(dllimport)
    #endif
#else
    #error Engine only support Windows
#endif

#define BIT(x) (1 << x)