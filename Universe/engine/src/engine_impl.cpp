/******************************************************************************
     * File: src/engine_impl.cpp
     * Description: Main engine interface implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "engine_impl.h"


namespace engine
{
    engine_ptr engine_ui::create()
    {
        return std::make_shared<engine_impl>();
    }

    engine_impl::engine_impl() : platform_instance(platform::platform_ui::create()) {}

    engine_impl::~engine_impl() {}

    window_ptr engine_impl::create_window(std::wstring name)
    {
        return std::make_shared<window_impl>(platform_instance, name);
    }
}
