/******************************************************************************
     * File: platform.windows.window_impl.cpp
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
        window_impl::window_impl(window_class& window_class_, std::wstring window_name)
        {
            //LPCTSTR class_name_LPCTSTR = static_cast<LPCTSTR>(class_name.c_str());
            LPCTSTR window_name_LPCTSTR = static_cast<LPCTSTR>(window_name.c_str());
            id = CreateWindow(
                class_name_LPCTSTR,  // Class name
                window_class_, // Name
                WS_OVERLAPPEDWINDOW, // Style
                CW_USEDEFAULT,       // Horizontal position
                CW_USEDEFAULT,       // Vertical position
                CW_USEDEFAULT,       // Width
                CW_USEDEFAULT,       // Height
                NULL,                // Parent handler
                NULL,                // Menu handler
                NULL,                // Module handler
                NULL                 // Window creation data
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
