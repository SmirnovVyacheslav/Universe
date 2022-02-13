/******************************************************************************
     * File: platform/windows/window_impl.h
     * Description: Platform window implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "../macros.h"

#pragma once
#ifdef PLATFORM_WINDOWS

#ifndef PLATFORM_WINDOW_IMPL_H
#define PLATFORM_WINDOW_IMPL_H

#include <windows.h>


namespace engine
{
    namespace platform
    {
        class window_impl
        {
        public:
            window_impl();
            ~window_impl();

        private:
            HWND id;
        };
    }
}

#endif
#endif
