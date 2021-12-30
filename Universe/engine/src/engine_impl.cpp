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
        type_engine_impl::initialize();
        windows_manager = type_engine_impl::instance->windows_manager_impl;
    }
    type_engine::~type_engine()
    {
        type_engine_impl::terminate();
    }


    type_engine_impl* type_engine_impl::instance = nullptr;


    type_engine_impl::type_engine_impl()
    {
        // Initialize code
    }
    type_engine_impl::~type_engine_impl()
    {
        // Terminate code
    }
    void type_engine_impl::initialize()
    {
        if (instance == nullptr)
        {
            instance = new type_engine_impl;
        }

        instance->ref_count++;
    }
    void type_engine_impl::terminate()
    {
        instance->ref_count--;

        if (instance->ref_count == 0)
        {
            instance->~type_engine_impl();
            instance = nullptr;
        }
    }
}
