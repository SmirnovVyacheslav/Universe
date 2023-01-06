// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/platform/window.h"
#include "src/platform/platform_def.h"
#include "src/core/data_type/std.h"
#include "src/core/data_type/string.h"

#ifdef WINDOWS
#include <windows.h>


namespace engine {
    namespace platform {
        LRESULT CALLBACK event_handler(HWND id, UINT message, WPARAM w_value, LPARAM l_value);


        class window::window_impl {
        public:
            window_impl(const string& name);

            HWND id();

            ~window_impl();
        private:
            HWND window_id;
            string window_name;
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

            window_impl(window_impl&& src) = delete;
            window_impl(const window_impl& src) = delete;

            void create_window();
            void show_window();
            void destroy_window();
            void register_window_class();
            void unregister_window_class();

            window_impl& operator=(window_impl&& src) = delete;
            window_impl& operator=(const window_impl& src) = delete;
        };
    }
}
#endif
