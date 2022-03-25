/******************************************************************************
     * File: window_ui.h
     * Description: API to work with windows
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef WINDOW_UI_H
#define WINDOW_UI_H

#include "src/platform/platform_ui.h"


namespace engine
{
	class window_obj_ui;
	class window_mng_ui;

    using window_obj_ptr = std::shared_ptr<window_obj_ui>;
	using window_mng_ptr = std::shared_ptr<window_mng_ui>;


    class window_obj_ui
    {
    public:
        virtual ~window_obj_ui() = default;

    protected:
		window_obj_ui() = default;
    };


	class window_mng_ui
	{
	public:
		virtual ~window_mng_ui() = default;

		static window_mng_ptr create(platform::platform_mng_ptr platform_instance);

		virtual window_obj_ptr create_window(std::wstring name) = 0;

	protected:
		window_mng_ui() = default;
	};
}

#endif
