/******************************************************************************
     * File: src/platform/windows/platform_impl.cpp
     * Description: Platform UI implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "platform_impl.h"

#ifdef PLATFORM_WINDOWS


namespace engine
{
    namespace platform
    {
        platform_impl::platform_impl() : window_data_instance(std::make_shared<window_data>()) {}

        platform_impl::~platform_impl() {}

        std::shared_ptr<platform_ui> platform_ui::create()
        {
            return std::make_shared<platform_impl>();
        }

        std::shared_ptr<window_ui> platform_impl::create_window(std::wstring name)
        {
            return std::make_shared<window_impl>(name, window_data_instance);
        }
    }
}

#endif
