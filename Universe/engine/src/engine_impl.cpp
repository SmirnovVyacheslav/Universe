/******************************************************************************
     * Description: Main engine interface implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "engine_impl.h"


namespace engine
{
    engine_mng_ui::engine_mng_ui() :
        window_mng(std::make_shared<window_mng_impl>(platform_mng_inst))
    {

    }

    engine_mng_ptr engine_mng_ui::create()
    {
        return std::make_shared<engine_mng_impl>();
    }


    engine_mng_impl::engine_mng_impl() :
        engine_mng_ui::window_mng(std::make_shared<window_mng_impl>(platform_mng_inst))
        platform_mng(platform::platform_mng_ui::create())
    {
        window_mng_inst = std::make_shared<window_mng_impl>(platform_mng_inst);
    }


    engine_mng_impl::~engine_mng_impl()
    {}
}
