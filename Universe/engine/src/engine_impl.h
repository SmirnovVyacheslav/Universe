/******************************************************************************
     * File: engine_impl.h
     * Description: Main engine interface implementation
     * Created: 07 Oct 2021
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/


#pragma once
#ifndef ENGINE_IMPL_H
#define ENGINE_IMPL_H


#include <cstdint>

#include "../include/engine.h"


namespace engine
{
    /*************************************************************************/
    class t_engine_impl : public t_engine
    {
    public:
        t_engine_impl();
        ~t_engine_impl();

        bool initialize();
        bool terminate();

    private:
        std::uint32_t ref_count = 0;
    };
    /*************************************************************************/
    t_engine_impl g_engine_instance;
    /*************************************************************************/
}

#endif
