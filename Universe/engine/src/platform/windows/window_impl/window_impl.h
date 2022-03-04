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

#include <windows.h>

#include "window_data.h"

namespace engine
{
    namespace platform
    {
        class window_impl
        {
        public:
            window_impl(std::wstring window_name, window_data window_data);
            ~window_impl();

        private:
            std::wstring name;
            HWND id;
        };
    }
}

#endif
#endif
