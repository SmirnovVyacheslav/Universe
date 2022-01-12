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

#include "../include/engine.h"
#include "window_impl.h"


namespace engine
{
    class type_engine_impl: public type_engine
    {
    public:
        static type_engine_impl& initialize();
        static void terminate();

    private:
        static type_engine_impl* instance;

        type_engine_impl();
        ~type_engine_impl();
        type_engine_impl(const type_engine_impl&) = delete;
        type_engine_impl& operator=(const type_engine_impl&) = delete;
    };
}

#endif
