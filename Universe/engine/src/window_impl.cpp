/******************************************************************************
     * Description: Windows implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/


#include "window_impl.h"


namespace engine
{
    window_obj_impl::window_obj_impl(platform::window_obj_ptr platform_window_inst) :
        platform_window_inst(platform_window_inst)
    {}


    window_obj_impl::~window_obj_impl()
    {}


    window_mng_impl::window_mng_impl(platform::platform_mng_ptr platform_mng_inst) :
        platform_mng_inst(platform_mng_inst)
    {}


    window_mng_impl::~window_mng_impl()
    {}


    window_obj_ptr window_mng_impl::create_window(std::wstring name)
    {
        return std::make_shared<window_obj_impl>(platform_mng_inst->window_mng->create_window(name));
    }
}
