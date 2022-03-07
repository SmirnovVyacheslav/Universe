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
    std::shared_ptr<engine_ui> engine_ui::create()
    {
        return std::make_shared<engine_impl>();
    }

    engine_impl::engine_impl() : platform_instance(platform::platform_ui::create()) {}

    engine_impl::~engine_impl() {}

    std::shared_ptr<window::window_ui> engine_impl::create_window(std::wstring name)
    {
        return std::make_shared<window::window_impl>(platform_instance, name);
    }

    //type_engine::type_engine() : windows_manager(*(new window::type_windows_manager_impl))
    //{
    //    // Initialize code
    //}
    //type_engine::~type_engine()
    //{
    //    // Terminate code
    //    dynamic_cast<window::type_windows_manager_impl*>(&windows_manager)->~type_windows_manager_impl();
    //}
    //type_engine& type_engine::initialize()
    //{
    //    return type_engine_impl::initialize();
    //}
    //type_engine& type_engine::instance()
    //{
    //    return type_engine_impl::initialize();
    //}
    //void type_engine::terminate()
    //{
    //    type_engine_impl::terminate();
    //}


    //type_engine_impl* type_engine_impl::instance = nullptr;
    //type_engine_impl::type_engine_impl()
    //{
    //    // Initialize code
    //}
    //type_engine_impl::~type_engine_impl()
    //{
    //    // Terminate code
    //}
    //type_engine_impl& type_engine_impl::initialize()
    //{
    //    if (instance == nullptr)
    //    {
    //        instance = new type_engine_impl;
    //    }
    //    return *instance;
    //}
    //void type_engine_impl::terminate()
    //{
    //    instance->~type_engine_impl();
    //    instance = nullptr;
    //}
}
