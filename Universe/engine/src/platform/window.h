/******************************************************************************
     * File: platform/window.h
     * Description: Platform window implementation
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
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

        private:
            class type_window_impl;
            std::unique_ptr<type_window_impl> window_impl;
        };
    }
}

#endif
