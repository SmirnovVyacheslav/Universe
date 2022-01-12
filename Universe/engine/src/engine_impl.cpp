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
        return type_engine_impl::initialize();
    }
    type_engine& type_engine::instance()
    {
        return type_engine_impl::initialize();
    }
    void type_engine::terminate()
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
    type_engine_impl& type_engine_impl::initialize()
    {
        if (instance == nullptr)
        {
            instance = new type_engine_impl;
        }
        return *instance;
    }
    void type_engine_impl::terminate()
    {
        instance->~type_engine_impl();
        instance = nullptr;
    }
}
