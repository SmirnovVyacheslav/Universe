/******************************************************************************
     * File: engine_impl.cpp
     * Description: Main engine interface implementation
     * Created: 07 Oct 2021
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/


#include "engine_impl.h"


namespace engine
{
    /*************************************************************************/
    t_engine::t_engine() : impl(g_engine_instance)
    {
        g_engine_instance.initialize();
    }

    t_engine::~t_engine()
    {
        g_engine_instance.terminate();
    }
    /*************************************************************************/
    t_engine_impl::t_engine_impl()
    {
        // Pass
    }

    t_engine_impl::~t_engine_impl()
    {
        if (ref_count != 0)
        {
            ref_count = 1;
            terminate();
        }
    }

    bool t_engine_impl::initialize()
    {
        if (ref_count == 0)
        {
            // Initialize code
        }

        ref_count++;
        return true;
    }

    bool t_engine_impl::terminate()
    {
        ref_count--;
        if (ref_count == 0)
        {
            // Terminate code
        }
        return true;
    }
    /*************************************************************************/
}
