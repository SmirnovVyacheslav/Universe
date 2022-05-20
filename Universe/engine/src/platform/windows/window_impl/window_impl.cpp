/******************************************************************************
     * Description: Platform window implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/


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


        window_obj_impl::window_obj_impl(std::wstring window_name, window_descriptor window_descriptor) : name(window_name)
        {
            id = CreateWindow(
                // Window class name
                static_cast<LPCTSTR>(window_descriptor.descriptor_name().c_str()),
                // Window name
                static_cast<LPCTSTR>(window_name.c_str()),
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


        window_obj_impl::~window_obj_impl()
        {
            DestroyWindow(id);
        }


        window_mng_ptr window_mng_ui::create()
        {
            return std::make_shared<window_mng_impl>();
        }


        window_mng_impl::window_mng_impl() :
            default_descriptor(window_descriptor(std::wstring(L"default_class"), default_handler))
        {}


        window_mng_impl::~window_mng_impl() {}


        window_obj_ptr window_mng_impl::create_window(std::wstring name)
        {
            return std::make_shared<window_obj_impl>(name, default_descriptor);
        }


        std::wstring window_mng_impl::default_descriptor_name()
        {
            return default_descriptor.descriptor_name();
        }


        HWND window_obj_impl::get_hwnd()
        {
            return id;
        }
    }
}

#endif
