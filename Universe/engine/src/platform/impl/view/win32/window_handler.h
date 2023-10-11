// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#ifdef platform_windows
#include <windows.h>
#endif


namespace engine::platform::view::win32
{
    #ifdef platform_windows

    LRESULT CALLBACK window_handler(HWND id, UINT message, WPARAM w_value, LPARAM l_value);

    #endif
}
