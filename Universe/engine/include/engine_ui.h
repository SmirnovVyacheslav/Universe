/******************************************************************************
     * File: engine_ui.h
     * Description: Main engine interface
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

/* ***************************************************************************
 * Name convention
 * ***************************************************************************
 * type_name   = data type / class
 * const_name  = global constant
 * global_name = global variable
 * this.name   = data type member
 * interface   = interface
 */

#pragma once
#ifndef ENGINE_UI_H
#define ENGINE_UI_H

#include <memory>
#include <string>

#include "window_ui.h"


namespace engine
{
    class engine_ui
    {
    public:
        //static type_engine& initialize();
        //static type_engine& instance();
        //static void terminate();
        static std::shared_ptr<engine_ui> create();

        virtual std::shared_ptr<window::window_ui> create_window(std::wstring name) = 0;
        //window::type_windows_manager& windows_manager;

    protected:
        engine_ui() = default;
        ~engine_ui() = default;
        //type_engine(const type_engine&) = delete;
        //type_engine& operator=(const type_engine&) = delete;
    };
}

#endif

// error handle
// print in log and other register output
// error code, severity and message
// clean resource
// throw exception
// client should catch for call function
