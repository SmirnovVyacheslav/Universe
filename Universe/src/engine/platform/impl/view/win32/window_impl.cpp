// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "engine/platform/impl/view/win32/window_impl.h"

#include "engine/def/platform.h"


namespace engine::platform::view::win32
{
    #ifdef windows

    window_impl::window_impl()
    {
        init_window_class();
        init_window();
        show_window();
    }

    void* window_impl::id()
    {
        return reinterpret_cast<void*>(hwnd);
    }

    window_impl::~window_impl()
    {
        term_window();
        term_window_class();
    }

    void window_impl::init_window()
    {
        hwnd = CreateWindow(
            static_cast<LPCTSTR>(window_class_cfg.name.w_str().c_str()),
            static_cast<LPCTSTR>(view_cfg.name.w_str().c_str()),
            window_cfg.style,
            window_cfg.horizontal_pos,
            window_cfg.vertical_pos,
            view_cfg.width,
            view_cfg.height,
            window_cfg.parent_id,
            window_cfg.menu,
            window_cfg.handler,
            window_cfg.creation_data
        );
        if (!hwnd)
        {
            throw string(u8"Failed to create window");
        }
    }

    void window_impl::show_window()
    {
        ShowWindow(hwnd, SW_SHOWNORMAL);
    }

    void window_impl::term_window()
    {
        DestroyWindow(hwnd);
    }

    void window_impl::init_window_class()
    {
        WNDCLASSEX data;
        std::wstring name = window_class_cfg.name.w_str();

        data.cbSize = sizeof(WNDCLASSEX);
        data.style = window_class_cfg.style;
        data.lpfnWndProc = window_handler;
        data.cbClsExtra = window_class_cfg.extra_memory;
        data.cbWndExtra = window_class_cfg.extra_memory;
        data.hIcon = window_class_cfg.icon;
        data.hCursor = window_class_cfg.cursor;
        data.hbrBackground = window_class_cfg.background;
        data.lpszMenuName = window_class_cfg.menu_name;
        data.lpszClassName = static_cast<LPCTSTR>(name.c_str());

        if (!RegisterClassEx(&data))
        {
            throw string(u8"Failed to register window class");
        }
    }

    void window_impl::term_window_class()
    {
        UnregisterClass(static_cast<LPCTSTR>(window_class_cfg.name.w_str().c_str()), GetModuleHandle(nullptr));
    }

    #endif
}
