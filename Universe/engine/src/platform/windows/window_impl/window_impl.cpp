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
		window_obj_impl::window_obj_impl(std::wstring window_name, std::shared_ptr<window_descriptor> window_descriptor) : name(window_name)
        {
            id = CreateWindow(
                // Window class name
                static_cast<LPCTSTR>(window_descriptor->descriptor_name().c_str()),
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
    }
}

#endif
