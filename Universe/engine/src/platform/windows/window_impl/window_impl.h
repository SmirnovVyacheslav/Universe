// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.


#include "src/platform/platform_def.h"


#pragma once
#ifdef WINDOWS
#ifndef PLATFORM_WINDOW_IMPL_H
#define PLATFORM_WINDOW_IMPL_H


#include <windows.h>
#include "window_handler.h"
#include "window_descriptor.h"
#include "src/platform/window.h"


namespace engine
{
    namespace platform
    {
        class window_impl
        {
        public:
            window_impl(string name);
            ~window_impl();

            HWND get_handler();

        private:
            HWND id;
            string name;
        };
    }
}

#endif
#endif
