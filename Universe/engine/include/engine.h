/******************************************************************************
     * File: engine.h
     * Description: Main engine interface
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

/* ***************************************************************************
 * Name convention
 * ***************************************************************************
 * t_name = data type / class
 * c_name = global constant
 * g_name = global variable
 * m_name = data type member
 *
 * type_name = data type / class
 * const_name = global constant
 * global_name = global variable
 * this.name = data type member
 * interface = interface
 */

#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "window.h"


namespace engine
{
    // Interface
    class type_engine
    {
    public:
        static type_engine& initialize();
        static type_engine& instance();
        static void terminate();

    protected:
        type_engine();
        ~type_engine();
        type_engine(const type_engine&) = delete;
        type_engine& operator=(const type_engine&) = delete;
    };
}

#endif
