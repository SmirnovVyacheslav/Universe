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
    class engine_mng_impl: public engine_mng_ui
    {
    public:
		engine_mng_impl();
        ~engine_mng_impl();

    private:
        platform::platform_mng_ptr platform_instance;
    };
}

#endif
