// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/platform/impl/view/win32/window_handler.h"

#include "engine/platform/api/event.h"


namespace engine::platform::view::win32
{
    #ifdef platform_windows

    LRESULT CALLBACK window_handler(HWND id, UINT message, WPARAM w_value, LPARAM l_value)
    {
        PAINTSTRUCT ps;
        HDC hdc;

        switch (message)
        {
            case WM_CREATE:
            {
                return 0;
            }

            case WM_PAINT:
            {
                hdc = BeginPaint(id, &ps);
                EndPaint(id, &ps);
                return 0;
            }

            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
            {
                return 0;
            }

            case WM_KEYUP:
            case WM_SYSKEYUP:
            {
                switch (w_value)
                {
                    case VK_ESCAPE:
                    {
                        event::event_item item;
                        item.exit = true;
                        event::add(item);
                    }
                    break;
                }
                return 0;
            }

            case WM_SIZE:
            {
                return 0;
            }

            case WM_DESTROY:
            {
                event::event_item item;
                item.exit = true;
                event::add(item);

                PostQuitMessage(0);
                return 0;
            }

            default:
            {
                return DefWindowProc(id, message, w_value, l_value);
            }
        }

        return 0;
    }

    #endif
}
