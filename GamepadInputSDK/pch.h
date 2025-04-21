
#ifndef PCH_H
#define PCH_H

#ifdef _WIN32
    #ifdef GAMEPAD_EXPORTS
        #define GAMEPAD_API __declspec(dllexport)
    #else
        #define GAMEPAD_API __declspec(dllimport)
    #endif
#else
    #define GAMEPADSDK_API
#endif

#include "framework.h"

#endif //PCH_H
