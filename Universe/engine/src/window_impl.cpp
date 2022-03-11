/******************************************************************************
     * File: src/window_impl.cpp
     * Description: Windows implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "window_impl.h"


namespace engine
{
    window_impl::window_impl(std::shared_ptr<platform::platform_ui> platform_instance, std::wstring name) :
        name(name)
    {
        window_instance = platform_instance->create_window(name);
    }

    window_impl::~window_impl() {}
}
