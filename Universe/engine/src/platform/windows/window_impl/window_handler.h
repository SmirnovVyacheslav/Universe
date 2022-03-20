/******************************************************************************
     * File: src/platform/windows/window_impl/window_handler.h
     * Description: Window handler
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "src/platform/macros_def.h"

#pragma once
#ifdef PLATFORM_WINDOWS
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
