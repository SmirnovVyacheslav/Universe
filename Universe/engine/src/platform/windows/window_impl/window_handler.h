// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.


#include "src/platform/platform_def.h"


#pragma once
#ifdef WINDOWS
#ifndef PLATFORM_WINDOW_HANDLER_H
#define PLATFORM_WINDOW_HANDLER_H


#include <windows.h>


namespace engine
{
    namespace platform
    {
        LRESULT CALLBACK default_handler(HWND id, UINT message, WPARAM w_value, LPARAM l_value);
    }
}

#endif
#endif
