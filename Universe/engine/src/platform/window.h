/******************************************************************************
     * File: platform.window.h
     * Description: Platform window implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef PLATFOM_WINDOW_H
#define PLATFOM_WINDOW_H

#include<memory>


namespace engine
{
    namespace platform
    {
        class type_window
        {
        public:
            type_window();
            ~type_window();

            //// Register class
            //WNDCLASSEX wcex;
            //wcex.cbSize = sizeof(WNDCLASSEX);
            //wcex.style = CS_HREDRAW | CS_VREDRAW;
            //wcex.lpfnWndProc = msg_handler;
            //wcex.cbClsExtra = 0;
            //wcex.cbWndExtra = 0;
            //wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
            //wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            //wcex.lpszMenuName = NULL;
            //wcex.lpszClassName = L"Header";
            //if (!RegisterClassEx(&wcex));
            ////return E_FAIL;
            //// Create window
            //RECT rc = { 0, 0, 533, 400 };
            //AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

            // ShowWindow(id, SW_SHOW);

        private:
            class type_window_impl;
            std::unique_ptr<type_window_impl> window_impl;
        };
    }
}

#endif
