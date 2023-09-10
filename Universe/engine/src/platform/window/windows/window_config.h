// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#ifdef platform_windows
#include <windows.h>

#include "src/core/data_type/string.h"


namespace engine::platform::window
{
    struct window_config
    {
        string class_name = u8"engine_window_class";

        DWORD window_style = WS_OVERLAPPEDWINDOW;
        int_32 horizontal_position = CW_USEDEFAULT;
        int_32 vertical_position = CW_USEDEFAULT;
        HWND parent_id = NULL;
        HMENU menu = NULL;
        HINSTANCE handler = NULL;
        LPVOID creation_data = NULL;

        UINT style = CS_HREDRAW | CS_VREDRAW;
        int_32 extra_memory = 0;
        HICON icon = LoadIcon(NULL, IDI_APPLICATION);
        HCURSOR cursor = LoadCursor(NULL, IDC_ARROW);
        HBRUSH background = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
        LPCWSTR menu_name = NULL;

        string name = u8"Engine";
    };
}
#endif
