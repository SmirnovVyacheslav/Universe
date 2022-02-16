/******************************************************************************
     * File: platform.windows.window_impl.cpp
     * Description: Platform window implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "window_impl.h"

#ifdef PLATFORM_WINDOWS


namespace engine
{
    namespace platform
    {
        window_impl::window_impl(std::wstring class_name, std::wstring window_name)
        {
            LPCTSTR class_name_LPCTSTR = static_cast<LPCTSTR>(class_name.c_str());
            LPCTSTR window_name_LPCTSTR = static_cast<LPCTSTR>(window_name.c_str());
            id = CreateWindow(
                class_name_LPCTSTR,  // Class name
                window_name_LPCTSTR, // Name
                WS_OVERLAPPEDWINDOW, // Style
                CW_USEDEFAULT,       // Horizontal position
                CW_USEDEFAULT,       // Vertical position
                CW_USEDEFAULT,       // Width
                CW_USEDEFAULT,       // Height
                NULL,                // Parent handler
                NULL,                // Menu handler
                NULL,                // Module handler
                NULL                 // Window creation data
            );
            if (!id)
            {
                throw std::wstring(L"Failed to create window");
            }
        }

        window_impl::~window_impl()
        {
            DestroyWindow(id);
        }




        LRESULT CALLBACK window_proceure(HWND id, UINT message, WPARAM w_value, LPARAM l_value)
        {
            switch (message)
            {
            case WM_CREATE:
                // Initialize the window. 
                return 0;

            case WM_PAINT:
                // Paint the window's client area. 
                return 0;

            case WM_SIZE:
                // Set the size and position of the window. 
                return 0;

            case WM_DESTROY:
                // Clean up window-specific data objects. 
                return 0;

                // 
                // Process other messages.
                // 

            default:
                return DefWindowProc(id, message, w_value, l_value);
            }
            return 0;
        }




        window_class::window_class(LRESULT CALLBACK window_proceure)
        {
            WNDCLASSEX init_data;

            init_data.cbSize = sizeof(WNDCLASSEX);            // Size of structure
            init_data.style = CS_HREDRAW | CS_VREDRAW;        // Redraw if size changes
            init_data.lpfnWndProc = window_proceure;
            init_data.cbClsExtra = 0;                         // no extra class memory 
            init_data.cbWndExtra = 0;                          // no extra window memory 
            wcx.hInstance = hinstance;         // handle to instance 
            wcx.hIcon = LoadIcon(NULL,
                IDI_APPLICATION);              // predefined app. icon 
            wcx.hCursor = LoadCursor(NULL,
                IDC_ARROW);                    // predefined arrow 
            wcx.hbrBackground = GetStockObject(
                WHITE_BRUSH);                  // white background brush 
            wcx.lpszMenuName = "MainMenu";    // name of menu resource 
            wcx.lpszClassName = "MainWClass";  // name of window class 
            if (!RegisterClassEx(&class_structure));
            //return E_FAIL;
        }

        window_class::~window_class()
        {

        }



        init::init()
        {

        }


        init::~init()
        {

        }
    }
}

#endif
