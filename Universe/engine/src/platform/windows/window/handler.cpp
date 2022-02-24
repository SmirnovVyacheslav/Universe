/******************************************************************************
     * File: src/platform/windows/window/handler.cpp
     * Description: Window handler
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "handler.h"

#ifdef PLATFORM_WINDOWS


namespace engine
{
    namespace platform
    {
        LRESULT CALLBACK default_handler(HWND id, UINT message, WPARAM w_value, LPARAM l_value)
        {
            switch (message)
            {
            case WM_CREATE:
                // Initialize the window.
                return 0;

            case WM_PAINT:
                // Paint the window's client area.
                return 0;

            case WM_SIZE:
                // Set the size and position of the window.
                return 0;

            case WM_DESTROY:
                // Clean up window-specific data objects.
                return 0;

                //
                // Process other messages.
                //

            default:
                return DefWindowProc(id, message, w_value, l_value);
            }
            return 0;
        }
    }
}

#endif
