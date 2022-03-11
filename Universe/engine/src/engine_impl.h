/******************************************************************************
     * File: src/engine_impl.h
     * Description: Main engine interface implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef ENGINE_IMPL_H
#define ENGINE_IMPL_H

#include <memory>

#include "engine_ui.h"
#include "window_impl.h"
#include "src/platform/platform_ui.h"


namespace engine
{
    class engine_impl: public engine_ui
    {
    public:
        engine_impl();
        ~engine_impl();

        window_ptr create_window(std::wstring name);

    private:
        platform::platform_ptr platform_instance;
    };
}

#endif
