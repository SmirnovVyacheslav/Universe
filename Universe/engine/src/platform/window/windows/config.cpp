// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#ifdef platform_windows
#include <windows.h>

#include "src/platform/window/config.h"
#include "src/core/data_type/std.h"
#include "src/core/data_type/string.h"


namespace engine::platform::window
{
    struct cofig_impl : public config
    {
        abstract_impl(cofig_impl)

        string window_class_name = u8"engine_window_class";

        DWORD window_style = WS_OVERLAPPEDWINDOW;
        int_32 horizontal_position = CW_USEDEFAULT;
        int_32 vertical_position = CW_USEDEFAULT;
        HWND window_parent_id = NULL;
        HMENU window_menu = NULL;
        HINSTANCE module_handler = NULL;
        LPVOID window_creation_data = NULL;

        UINT style = CS_HREDRAW | CS_VREDRAW;
        int_32 extra_memory = 0;
        HICON icon = LoadIcon(NULL, IDI_APPLICATION);
        HCURSOR cursor = LoadCursor(NULL, IDC_ARROW);
        HBRUSH background = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
        LPCWSTR menu_name = NULL;
    };

    config* init()
    {
        return new cofig_impl();
    }
}
#endif
