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
	class engine_mng_ui;
	
	using engine_mng_ptr=std::shared_ptr<engine_mng_ui>;


    class engine_mng_ui
    {
    public:
        virtual ~engine_mng_ui() = default;

        static engine_mng_ptr create();

		window_mng_ptr window_mng;

    protected:
		engine_mng_ui() = default;
    };
}

#endif
