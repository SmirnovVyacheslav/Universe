/******************************************************************************
     * File: engine.h
     * Description: Main engine interface
     * Created: 07 Oct 2021
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
 */

#pragma once
#ifndef ENGINE_H
#define ENGINE_H

namespace engine
{
    /*************************************************************************/
    class t_engine
    {
    public:
        t_engine();
        ~t_engine();

    private:
        t_engine(const t_engine&) = delete;
        t_engine& operator=(const t_engine&) = delete;

        t_engine& impl;
    };
    /*************************************************************************/
}

#endif
