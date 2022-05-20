// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.


#include "window_handler.h"


#ifdef WINDOWS


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
