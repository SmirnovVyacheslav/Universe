// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#ifdef platform_windows
#include <windows.h>

namespace engine::platform::window
{
    LRESULT CALLBACK event_handler(HWND id, UINT message, WPARAM w_value, LPARAM l_value) {
        PAINTSTRUCT ps;
        HDC hdc;

        switch (message) {
        case WM_CREATE:
            // Initialize the window.
            return 0;
        case WM_PAINT:
            // Paint the window's client area.
            hdc = BeginPaint(id, &ps);
            EndPaint(id, &ps);
            return 0;
        case WM_SIZE:
            // Set the size and position of the window.
            return 0;
        case WM_DESTROY:
            // Clean up window-specific data objects.
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(id, message, w_value, l_value);
        }
        return 0;
    }
}

#endif

