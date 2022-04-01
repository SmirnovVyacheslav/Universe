/******************************************************************************
     * Description: Main engine interface implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/


#include "engine_impl.h"


namespace engine
{
	engine_mng_ptr engine_mng_ui::create()
    {
        return std::make_shared<engine_mng_impl>();
    }


	engine_mng_impl::engine_mng_impl() :
		platform_instance(platform::platform_mng_ui::create())
	{
		window_mng = window_mng_ui::create(platform_instance);
	}


	engine_mng_impl::~engine_mng_impl() {}
}
