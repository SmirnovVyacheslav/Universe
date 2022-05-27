// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/platform/platform_def.h"
#ifdef WINDOWS
#include <windows.h>
#include "src/platform/window.h"


namespace engine {
    namespace platform {
        LRESULT CALLBACK event_handler(HWND id, UINT message, WPARAM w_value, LPARAM l_value);


        class window_impl {
            public:
                window_impl(const string& name);
                ~window_impl();

                HWND id();
            private:
                HWND window_id;
                string window_name;
                string window_class_name = u8"engine_window_class";
                DWORD window_style = WS_OVERLAPPEDWINDOW;
                std::int32_t horizontal_position = CW_USEDEFAULT;
                std::int32_t vertical_position = CW_USEDEFAULT;
                HWND window_parent_id = NULL;
                HMENU window_menu = NULL;
                HINSTANCE module_handler = NULL;
                LPVOID window_creation_data = NULL;

                UINT style = CS_HREDRAW | CS_VREDRAW;
                std::int32_t extra_memory = 0;
                HICON icon = LoadIcon(NULL, IDI_APPLICATION);
                HCURSOR cursor = LoadCursor(NULL, IDC_ARROW);
                HBRUSH background = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
                LPCWSTR menu_name = NULL;

                void create_window();
                void show_window();
                void destroy_window();
                void register_window_class();
                void unregister_window_class();

                window_impl(window_impl&& src) = delete;
                window_impl(const window_impl& src) = delete;
                window_impl& operator=(window_impl&& src) = delete;
                window_impl& operator=(const window_impl& src) = delete;
        };
    }
}
#endif
