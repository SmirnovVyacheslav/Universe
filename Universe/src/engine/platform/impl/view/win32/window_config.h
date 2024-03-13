// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/def/platform.h"
#include "engine/var/string.h"

#ifdef windows
#include <windows.h>
#endif


namespace engine::platform::view::win32
{
    #ifdef windows

    struct window_config
    {
        DWORD style = WS_OVERLAPPEDWINDOW;
        int32 horizontal_pos = CW_USEDEFAULT;
        int32 vertical_pos = CW_USEDEFAULT;
        HWND parent_id = NULL;
        HMENU menu = NULL;
        HINSTANCE handler = NULL;
        LPVOID creation_data = NULL;
    };

    struct window_class_config
    {
        string name = u8"view_window_class";
        UINT style = CS_HREDRAW | CS_VREDRAW;
        int32 extra_memory = 0;
        HICON icon = LoadIcon(NULL, IDI_APPLICATION);
        HCURSOR cursor = LoadCursor(NULL, IDC_ARROW);
        HBRUSH background = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
        LPCWSTR menu_name = NULL;
    };

    #endif
}
