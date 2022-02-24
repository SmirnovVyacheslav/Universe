/******************************************************************************
     * File: src/platform/windows/window/descriptor.cpp
     * Description: Window desciptor
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "descriptor.h"

#ifdef PLATFORM_WINDOWS


namespace engine
{
    namespace platform
    {
        descriptor::descriptor(std::wstring name, LRESULT(*handler)(HWND, UINT, WPARAM, LPARAM)) : name(name)
        {
            WNDCLASSEX data;

            data.cbSize = sizeof(WNDCLASSEX);
            // Redraw if size changes
            data.style = CS_HREDRAW | CS_VREDRAW;
            // Window procedure
            data.lpfnWndProc = handler;
            // Extra class memory
            data.cbClsExtra = 0;
            data.cbWndExtra = 0;
            // Instance handler
            data.hInstance = GetModuleHandle(nullptr);
            // Window icon and cursor
            data.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            data.hCursor = LoadCursor(NULL, IDC_ARROW);
            // Window background brush
            data.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
            // Name of menu resource
            data.lpszMenuName = NULL;
            // Name of window class
            data.lpszClassName = static_cast<LPCTSTR>(name.c_str());

            if (!RegisterClassEx(&data))
            {
                throw std::wstring(L"Failed to register window class");
            }
        }

        descriptor::~descriptor()
        {
            UnregisterClass(static_cast<LPCTSTR>(name.c_str()), GetModuleHandle(nullptr));
        }
    }
}

#endif
