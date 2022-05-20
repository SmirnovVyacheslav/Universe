// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.


#include "src/platform/platform_def.h"


#pragma once
#ifdef WINDOWS
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
