// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.


#include "window_impl.h"


#ifdef WINDOWS


namespace engine
{
    namespace platform
    {
        window window::inst = window();

        void window::create_window(string name)
        {
            inst.window_inst = new window_impl(name);
        }

        void* window::get_handler()
        {
            return inst.window_inst->get_handler();
        }

        window_impl::window_impl(string name) :
            name(name)
        {
            window_descriptor desriptor(std::wstring(L"default_class"), default_handler);

            id = CreateWindow(
                // Window class name
                static_cast<LPCTSTR>(desriptor.descriptor_name().c_str()),
                // Window name
                static_cast<LPCTSTR>(name.w_str().c_str()),
                // Style
                WS_OVERLAPPEDWINDOW,
                // Horizontal position
                CW_USEDEFAULT,
                // Vertical position
                CW_USEDEFAULT,
                // Width
                800, //CW_USEDEFAULT,
                // Height
                600, //CW_USEDEFAULT,
                // Parent handler
                NULL,
                // Menu handler
                NULL,
                // Module handler
                NULL,
                // Window creation data
                NULL
            );
            if (!id)
            {
                throw std::wstring(L"Failed to create window");
            }

            ShowWindow(id, SW_SHOWNORMAL);
        }

        window_impl::~window_impl()
        {
            DestroyWindow(id);
        }

        HWND window_impl::get_handler()
        {
            return id;
        }
    }
}

#endif
