/******************************************************************************
     * Description: Windows implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/


#include "window_impl.h"


namespace engine
{
	window_obj_impl::window_obj_impl(platform::platform_mng_ptr platform_instance, std::wstring name) :
		window_instance(platform_instance->window_mng->create_window(name)), name(name)
	{}


	window_obj_impl::~window_obj_impl() {}


	window_mng_impl::window_mng_impl(platform::platform_mng_ptr platform_instance) :
		platform_instance(platform_instance)
	{}


	window_mng_impl::~window_mng_impl() {}


	window_obj_ptr window_mng_impl::create_window(std::wstring name)
	{
		return std::make_shared<window_obj_impl>(platform_instance, name);
	}


	window_mng_ptr window_mng_ui::create(platform::platform_mng_ptr platform_instance)
	{
		return std::make_shared<window_mng_impl>(platform_instance);
	}
}
