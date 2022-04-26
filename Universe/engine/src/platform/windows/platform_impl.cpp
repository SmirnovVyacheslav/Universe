/******************************************************************************
     * File: src/platform/windows/platform_impl.cpp
     * Description: Platform UI implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "platform_impl.h"

#ifdef PLATFORM_WINDOWS


namespace engine
{
    namespace platform
    {
		platform_mng_impl::platform_mng_impl() {}

		platform_mng_impl::~platform_mng_impl() {}


		platform_mng_ptr platform_mng_ui::create()
		{
			return std::make_shared<platform_mng_impl>();
		}
    }
}

#endif