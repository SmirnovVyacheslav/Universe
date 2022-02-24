/******************************************************************************
     * File: platform.windows.window_impl.h
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

#include <string>

#include <windows.h>

//LRESULT CALLBACK window_proceure(HWND id, UINT message, WPARAM w_value, LPARAM l_value);
namespace engine
{
    namespace platform
    {
        class window_impl
        {
        public:
            window_impl(std::wstring class_name, std::wstring window_name);
            ~window_impl();

        private:
            HWND id;
        };
    }
}

#endif
#endif
