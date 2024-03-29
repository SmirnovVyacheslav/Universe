// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/def/platform.h"
#include "engine/core/def/class_format.h"
#include "engine/core/def/abstract_class.h"

#include "engine/platform/api/view.h"
#include "engine/platform/impl/view/window.h"
#include "engine/platform/impl/view/win32/window_config.h"
#include "engine/platform/impl/view/win32/window_handler.h"

#ifdef windows
#include <windows.h>
#endif


namespace engine::platform::view::win32
{
    #ifdef windows

    class window_impl : public window
    {
        abstract_impl(window_impl)
        ____________________public____________________
        window_impl();
        window_impl(window_impl&& src) = delete;
        window_impl(const window_impl& src) = delete;

        void* id();

        window_impl& operator=(window_impl&& src) = delete;
        window_impl& operator=(const window_impl& src) = delete;

        ~window_impl();
        ____________________private___________________
        HWND hwnd;
        view_config view_cfg;
        window_config window_cfg;
        window_class_config window_class_cfg;

        void init_window();
        void show_window();
        void term_window();
        void init_window_class();
        void term_window_class();
    };

    #else

    class window_impl : public window
    {
        abstract_impl(window_impl)
        ____________________public____________________
        window_impl() = deault;
        window_impl(window_impl&& src) = delete;
        window_impl(const window_impl& src) = delete;

        void* id() { return nullptr; };

        window_impl& operator=(window_impl&& src) = delete;
        window_impl& operator=(const window_impl& src) = delete;

        ~window_impl() = deault;
    };

    #endif
}
