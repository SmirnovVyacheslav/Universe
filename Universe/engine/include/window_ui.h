/******************************************************************************
     * Description: API to work with window
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef WINDOW_UI_H
#define WINDOW_UI_H

#include "std_include.h"


namespace engine
{
    class window_obj_ui;
    class window_mng_ui;
    using window_obj_ptr = std::shared_ptr<window_obj_ui>;
    using window_mng_ptr = std::shared_ptr<window_mng_ui>;


    class window_obj_ui
    {
    protected:
        window_obj_ui() = default;
        virtual ~window_obj_ui() = default;
    };


    class window_mng_ui
    {
    public:
        virtual window_obj_ptr create_window(std::wstring name) = 0;

    protected:
        window_mng_ui() = default;
        virtual ~window_mng_ui() = default;
    };
}
#endif
