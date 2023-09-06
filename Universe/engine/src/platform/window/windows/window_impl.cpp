// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#ifdef platform_windows
#include "src/platform/window/window.h"
#include "src/platform/window/windows/handler.h"


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

        ~window_impl() = default;

    private:
        HWND hwnd;

        void create_window();
        void destroy_window();
        void show_window();
        void register_window_class();
        void unregister_window_class();
    };
    

    window* init(config* cfg)
    {
        return new window_impl(cfg);
    }


    window::window() {
    }
    void window::create_window() {
        inst.impl.initialize(config::core()->window_name);
    }
    void* window::id() {
        return inst.impl->id();
    }
    window::~window() {
    }

    window::window_impl::window_impl(const string& name) :
        window_name(name) {
        create_window();
        show_window();
    }
    window::window_impl::~window_impl() {
        destroy_window();
    }
    HWND window::window_impl::id() {
        return window_id;
    }
    void window::window_impl::create_window() {
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
    void window::window_impl::show_window() {
        ShowWindow(window_id, SW_SHOWNORMAL);
    }
    void window::window_impl::destroy_window() {
        DestroyWindow(window_id);
        unregister_window_class();
    }
    void window::window_impl::register_window_class() {
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
    void window::window_impl::unregister_window_class() {
        UnregisterClass(static_cast<LPCTSTR>(window_class_name.w_str().c_str()), GetModuleHandle(nullptr));
    }
}
#endif
