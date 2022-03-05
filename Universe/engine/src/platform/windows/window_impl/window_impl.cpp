/******************************************************************************
     * File: src/platform/windows/window_impl/window_impl.cpp
     * Description: Platform window implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "window_impl.h"

#ifdef PLATFORM_WINDOWS


namespace engine
{
    namespace platform
    {
        std::shared_ptr<window_ui> window_ui::create(std::wstring name)
        {
            return std::make_shared<window_impl>(name, );
        }


        window_impl::window_impl(std::wstring window_name, window_data window_data) : name(window_name)
        {
            id = CreateWindow(
                // Window class name
                static_cast<LPCTSTR>(window_data.default_descriptor_name().c_str()),
                // Window name
                static_cast<LPCTSTR>(window_name.c_str()),
                // Style
                WS_OVERLAPPEDWINDOW,
                // Horizontal position
                CW_USEDEFAULT,
                // Vertical position
                CW_USEDEFAULT,
                // Width
                CW_USEDEFAULT,
                // Height
                CW_USEDEFAULT,
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
        }

        window_impl::~window_impl()
        {
            DestroyWindow(id);
        }
    }
}

#endif
