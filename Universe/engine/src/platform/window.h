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
        class window_impl;




        class window
        {
        public:
            window();
            ~window();
            //// Create window
            //RECT rc = { 0, 0, 533, 400 };
            //AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

            // ShowWindow(id, SW_SHOW);

        private:
            std::unique_ptr<window_impl> window_impl;
        };
    }
}

#endif
