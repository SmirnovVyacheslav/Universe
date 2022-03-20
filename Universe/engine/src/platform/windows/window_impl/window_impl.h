/******************************************************************************
     * File: src/platform/windows/window_impl/window_impl.h
     * Description: Platform window implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "src/platform/macros_def.h"

#pragma once
#ifdef PLATFORM_WINDOWS
#ifndef PLATFORM_WINDOW_IMPL_H
#define PLATFORM_WINDOW_IMPL_H

#include <string>
#include <memory>

#include <windows.h>

#include "window_data.h"
#include "src/platform/window_ui.h"

namespace engine
{
    namespace platform
    {
        class window_impl: public window_ui
        {
        public:
            window_impl(std::wstring window_name, std::shared_ptr<window_data> window_data);
            ~window_impl();

        private:
            std::wstring name;
            HWND id;
        };
    }
}

#endif
#endif


/******************************************************************************
	 * File: src/platform/windows/window_impl/window_data.h
	 * Description: Window data
	 * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
	 * Author: Vyacheslav Smirnov
	 * Email: necrolazy@gmail.com
******************************************************************************/

#include "src/platform/macros_def.h"

#pragma once
#ifdef PLATFORM_WINDOWS
#ifndef PLATFORM_WINDOW_DATA_H
#define PLATFORM_WINDOW_DATA_H

#include <string>

#include <windows.h>

#include "window_handler.h"
#include "window_descriptor.h"


namespace engine
{
	namespace platform
	{
		class window_data
		{
		public:
			window_data();
			~window_data();
			std::wstring default_descriptor_name();

		private:
			window_descriptor default_descriptor;
		};
	}
}

#endif
#endif
