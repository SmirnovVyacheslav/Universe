/******************************************************************************
     * File: engine_impl.h
     * Description: Main engine interface implementation
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef ENGINE_IMPL_H
#define ENGINE_IMPL_H

#include <cstdint>

#include "../include/engine.h"
#include "window_impl.h"


namespace engine
{
    class type_engine_impl
    {
    public:
        static type_engine_impl* instance;

        window::type_windows_manager_impl* windows_manager_impl = nullptr;

        static void initialize();
        static void terminate();

    private:
        type_engine_impl();
        ~type_engine_impl();

        std::uint32_t ref_count = 0;
    };
}

#endif
