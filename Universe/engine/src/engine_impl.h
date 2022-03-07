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
        //static type_engine_impl& initialize();
        //static void terminate();

        engine_impl();
        ~engine_impl();

        std::shared_ptr<window::window_ui> create_window(std::wstring name);

    private:
        std::shared_ptr<platform::platform_ui> platform_instance;
        
        //static type_engine_impl* instance;

        /*type_engine_impl();
        ~type_engine_impl();
        type_engine_impl(const type_engine_impl&) = delete;
        type_engine_impl& operator=(const type_engine_impl&) = delete;*/
    };
}

#endif
