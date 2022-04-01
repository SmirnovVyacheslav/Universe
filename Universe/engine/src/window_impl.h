/******************************************************************************
     * Description: Windows implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/


#pragma once
#ifndef WINDOW_IMPL_H
#define WINDOW_IMPL_H


#include <memory>
#include <string>

#include "window_ui.h"
#include "src/platform/platform_ui.h"


namespace engine
{
	class window_obj_impl;
	class window_mng_impl;


    class window_obj_impl: public window_obj_ui
    {
    public:
		window_obj_impl(platform::platform_mng_ptr platform_instance, std::wstring name);
        ~window_obj_impl();

    private:
        std::wstring name;
        platform::window_obj_ptr window_instance;
    };


	class window_mng_impl : public window_mng_ui
	{
	public:
		window_mng_impl(platform::platform_mng_ptr platform_instance);
		~window_mng_impl();

		window_obj_ptr create_window(std::wstring name);

	private:
		platform::platform_mng_ptr platform_instance;
	};
}

#endif
