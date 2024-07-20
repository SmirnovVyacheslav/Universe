// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_impl_view.h"


namespace engine::core::view
{
#ifdef windows

    LRESULT CALLBACK window_handler(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
    {
        switch (msg)
        {
            case WM_CREATE:
            {
                return 0;
            }

            case WM_PAINT:
            {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                EndPaint(hwnd, &ps);
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
                switch (w_param)
                {
                    case VK_ESCAPE:
                    {
                        engine::core::event::obj event_obj =
                        {
                            .exit = true
                        };
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
                return DefWindowProc(hwnd, msg, w_param, l_param);
            }
        }

        return 0;
    }


    impl::impl()
    {

        WNDCLASSEX window_class_data = {
            .cbSize = sizeof(WNDCLASSEX),
            .style = CS_HREDRAW | CS_VREDRAW,
            .lpfnWndProc = window_handler,
            .cbClsExtra = 0,
            .cbWndExtra = 0,
            .hIcon = LoadIcon(NULL, IDI_APPLICATION),
            .hCursor = LoadCursor(NULL, IDC_ARROW),
            .hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)),
            .lpszMenuName = NULL,
            .lpszClassName = window_class_name
        };
        if (!RegisterClassEx(&window_class_data))
        {
            throw error("Failed to register window class");
        }

        hwnd = CreateWindow(
            window_class_name,
            window_name,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            settings::get().view.width,
            settings::get().view.height,
            NULL,
            NULL,
            NULL,
            NULL
        );
        if (!hwnd)
        {
            throw error("Failed to create window");
        }

        ShowWindow(hwnd, SW_SHOWNORMAL);
    }

    void* impl::id()
    {
        return reinterpret_cast<void*>(hwnd);
    }

    impl::~impl()
    {
        DestroyWindow(hwnd);
        UnregisterClass(window_class_name, GetModuleHandle(nullptr));
    }

#endif
}
