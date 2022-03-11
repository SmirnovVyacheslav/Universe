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
    using engine_ptr=std::shared_ptr<engine_ui>;

    class engine_ui
    {
    public:
        virtual ~engine_ui() = default;

        static engine_ptr create();

        virtual window_ptr create_window(std::wstring name) = 0;

    protected:
        engine_ui() = default;
    };
}

#endif
