// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#ifdef platform_windows
#include "src/platform/window/window.h"
#include "src/platform/window/windows/window_handler.h"
#include "src/platform/window/windows/window_config.h"


namespace engine::platform::window
{
    class window_impl : public window
    {
        abstract_impl(window_impl)

    public:
        window_impl(config* cfg);
        window_impl(window_impl&& src) = delete;
        window_impl(const window_impl& src) = delete;

        void* id();

        window_impl& operator=(window_impl&& src) = delete;
        window_impl& operator=(const window_impl& src) = delete;

        ~window_impl();

    private:
        HWND hwnd;
        config* cfg;
        window_config window_cfg;

        void init_window();
        void term_window();
        void show_window();
        void init_window_class();
        void term_window_class();
    };
}
#endif
