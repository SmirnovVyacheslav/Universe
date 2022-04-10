/******************************************************************************
     * Description: Windows implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef WINDOW_IMPL_H
#define WINDOW_IMPL_H

#include "window_ui.h"
#include "src/platform/platform_ui.h"


namespace engine
{
    class window_obj_impl: public window_obj_ui
    {
    public:
        window_obj_impl(platform::window_obj_ptr platform_window);
        ~window_obj_impl();

    private:
        const platform::window_obj_ptr platform_window;
    };


    class window_mng_impl : public window_mng_ui
    {
    public:
        window_mng_impl(platform::platform_mng_ptr platform_mng);
        ~window_mng_impl();

        window_obj_ptr create_window(std::wstring name);

    private:
        const platform::platform_mng_ptr platform_mng;
    };
}

#endif
