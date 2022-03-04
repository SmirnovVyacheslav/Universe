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
