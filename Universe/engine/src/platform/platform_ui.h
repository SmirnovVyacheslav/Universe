/******************************************************************************
     * File: src/platform/platform_ui.h
     * Description: Platform UI
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef PLATFORM_UI_H
#define PLATFORM_UI_H

#include <memory>

#include "src/platform/window_ui.h"


namespace engine
{
    namespace platform
    {
		class platform_mng_ui;

		using platform_mng_ptr = std::shared_ptr<platform_mng_ui>;


        class platform_mng_ui
        {
        public:
			virtual ~platform_mng_ui() = default;

            static platform_mng_ptr create();

			window_mng_ptr window_mng;

        protected:
			platform_mng_ui();
        };
    }
}

#endif