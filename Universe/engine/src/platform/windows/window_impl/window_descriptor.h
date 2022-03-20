/******************************************************************************
     * File: src/platform/windows/window_impl/window_descriptor.h
     * Description: Window desciptor
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "src/platform/macros_def.h"

#pragma once
#ifdef PLATFORM_WINDOWS
#ifndef PLATFORM_WINDOW_DESCRIPTOR_H
#define PLATFORM_WINDOW_DESCRIPTOR_H

#include <string>

#include <windows.h>


namespace engine
{
    namespace platform
    {
        class window_descriptor
        {
        public:
            window_descriptor(std::wstring name, LRESULT(*handler)(HWND, UINT, WPARAM, LPARAM));
            ~window_descriptor();

            std::wstring descriptor_name();

        private:
            std::wstring name;
        };
    }
}

#endif
#endif
