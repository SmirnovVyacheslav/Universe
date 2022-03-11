/******************************************************************************
     * File: src/window_impl.h
     * Description: Windows implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef WINDOW_IMPL_H
#define WINDOW_IMPL_H

#include <memory>
#include <string>

#include "window_ui.h"
#include "src/platform/platform_ui.h"
#include "src/platform/window_ui.h"


namespace engine
{
    class window_impl: public window_ui
    {
    public:
        window_impl(std::shared_ptr<platform::platform_ui> platform_instance, std::wstring name);
        ~window_impl();
    private:
        std::wstring name;
        std::shared_ptr<platform::window_ui> window_instance;
    };
}

#endif
