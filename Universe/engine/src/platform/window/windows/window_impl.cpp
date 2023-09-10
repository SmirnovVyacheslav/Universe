// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#ifdef platform_windows
#include "src/platform/window/windows/window_impl.h"


namespace engine::platform::window
{
    window* init(config* cfg)
    {
        return new window_impl(cfg);
    }


    window_impl::window_impl(config* cfg) : cfg(cfg)
    {
        init_window_class();
        init_window();
        show_window();
    }
    window_impl::~window_impl() {
        term_window();
        term_window_class();
    }
    void* window_impl::id() {
        return reinterpret_cast<void*>(hwnd);
    }
    void window_impl::init_window() {
        hwnd = CreateWindow(
            static_cast<LPCTSTR>(window_cfg.class_name.w_str().c_str()),
            static_cast<LPCTSTR>(cfg->name.w_str().c_str()),
            window_cfg.window_style,
            window_cfg.horizontal_position,
            window_cfg.vertical_position,
            cfg->width,
            cfg->height,
            window_cfg.parent_id,
            window_cfg.menu,
            window_cfg.handler,
            window_cfg.creation_data
        );
        if (!hwnd) {
            throw string(u8"Failed to create window");
        }
    }
    void window_impl::show_window() {
        ShowWindow(hwnd, SW_SHOWNORMAL);
    }
    void window_impl::term_window() {
        DestroyWindow(hwnd);
    }
    void window_impl::init_window_class() {
        WNDCLASSEX data;
        std::wstring name = window_cfg.class_name.w_str();

        data.cbSize = sizeof(WNDCLASSEX);
        data.style = window_cfg.style;
        data.lpfnWndProc = event_handler;
        data.cbClsExtra = window_cfg.extra_memory;
        data.cbWndExtra = window_cfg.extra_memory;
        data.hIcon = window_cfg.icon;
        data.hCursor = window_cfg.cursor;
        data.hbrBackground = window_cfg.background;
        data.lpszMenuName = window_cfg.menu_name;
        data.lpszClassName = static_cast<LPCTSTR>(name.c_str());

        if (!RegisterClassEx(&data)) {
            throw string(u8"Failed to register window class");
        }
    }
    void window_impl::term_window_class() {
        UnregisterClass(static_cast<LPCTSTR>(window_cfg.class_name.w_str().c_str()), GetModuleHandle(nullptr));
    }
}
#endif
