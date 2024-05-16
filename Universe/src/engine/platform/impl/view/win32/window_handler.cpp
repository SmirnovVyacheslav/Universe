// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/platform/impl/view/win32/window_handler.h"

#include "engine/def/platform.h"
#include "engine/core/event/api_event.h"
#include "engine/core/event/obj_event.h"


namespace engine::platform::view::win32
{
    #ifdef windows

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
                        engine::core::event::obj event_obj;
                        event_obj.exit = true;
                        engine::core::event::add(event_obj);
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
