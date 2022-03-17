/******************************************************************************
     * File: src/platform/windows/window_impl/window_data.cpp
     * Description: Window data
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "window_data.h"

#ifdef PLATFORM_WINDOWS


namespace engine
{
    namespace platform
    {
        window_data::window_data() :
            default_descriptor(window_descriptor(std::wstring(L"default_class"), default_handler))
        {}

        window_data::~window_data() {}

        std::wstring window_data::default_descriptor_name()
        {
            return default_descriptor.descriptor_name();
        }
    }
}

#endif
