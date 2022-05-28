// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#include "window_impl.h"

#ifdef WINDOWS


namespace engine {
    namespace platform {
        void* window::id() {
            return inst.impl->id();
        }
        void window::create_window() {
            inst.impl.initialize(config::core()->window_name);
        }


        LRESULT CALLBACK event_handler(HWND id, UINT message, WPARAM w_value, LPARAM l_value) {
            switch (message) {
                case WM_CREATE:
                    // Initialize the window.
                    return 0;
                case WM_PAINT:
                    // Paint the window's client area.
                    return 0;
                case WM_SIZE:
                    // Set the size and position of the window.
                    return 0;
                case WM_DESTROY:
                    // Clean up window-specific data objects.
                    return 0;
                default:
                    return DefWindowProc(id, message, w_value, l_value);
            }
            return 0;
        }


        window_impl::window_impl(const string& name) :
            window_name(name) {
            create_window();
            show_window();
        }
        window_impl::~window_impl() {
            destroy_window();
        }
        HWND window_impl::id() {
            return window_id;
        }
        void window_impl::create_window() {
            register_window_class();

            window_id = CreateWindow(
                static_cast<LPCTSTR>(window_class_name.w_str().c_str()),
                static_cast<LPCTSTR>(window_name.w_str().c_str()),
                window_style,
                horizontal_position,
                vertical_position,
                config::video()->window_width,
                config::video()->window_height,
                window_parent_id,
                window_menu,
                module_handler,
                window_creation_data
            );
            if (!window_id) {
                throw string(u8"Failed to create window");
            }
        }
        void window_impl::show_window() {
            ShowWindow(window_id, SW_SHOWNORMAL);
        }
        void window_impl::destroy_window() {
            DestroyWindow(window_id);
            unregister_window_class();
        }
        void window_impl::register_window_class() {
            WNDCLASSEX data;
            std::wstring name = window_class_name.w_str();

            data.cbSize = sizeof(WNDCLASSEX);
            data.style = style;
            data.lpfnWndProc = event_handler;
            data.cbClsExtra = extra_memory;
            data.cbWndExtra = extra_memory;
            data.hIcon = icon;
            data.hCursor = cursor;
            data.hbrBackground = background;
            data.lpszMenuName = menu_name;
            data.lpszClassName = static_cast<LPCTSTR>(name.c_str());

            if (!RegisterClassEx(&data)) {
                throw string(u8"Failed to register window class");
            }
        }
        void window_impl::unregister_window_class() {
            UnregisterClass(static_cast<LPCTSTR>(window_class_name.w_str().c_str()), GetModuleHandle(nullptr));
        }
    }
}
#endif
