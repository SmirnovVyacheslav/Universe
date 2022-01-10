/******************************************************************************
     * File: engine_impl.cpp
     * Description: Main engine interface implementation
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "engine_impl.h"


namespace engine
{
    type_engine::type_engine()
    {
        // Initialize code
    }
    type_engine::~type_engine()
    {
        // Terminate code
    }
    type_engine& type_engine::initialize()
    {
        return type_engine_impl::instance();
    }
    type_engine& type_engine::instance()
    {
        return type_engine_impl::instance();
    }
    void type_engine::terminate()
    {
        // Terminate code
    }

    type_engine_impl::type_engine_impl()
    {
        // Initialize code
    }
    type_engine_impl::~type_engine_impl()
    {
        // Terminate code
    }
    type_engine_impl& type_engine_impl::instance()
    {
        static type_engine_impl engine_instance;
        return engine_instance;
    }
}
