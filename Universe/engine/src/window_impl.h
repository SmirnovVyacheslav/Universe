/******************************************************************************
     * File: window_impl.h
     * Description: Windows implementation
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef WINDOW_IMPL_H
#define WINDOW_IMPL_H

#include <map>

#include "../include/window.h"


namespace engine
{
    namespace window
    {
        class type_window_impl: public type_window
        {
        public:
            type_window_impl();
            ~type_window_impl();
        };


        class type_windows_manager_impl : public type_windows_manager
        {
        public:
            type_windows_manager_impl();
            ~type_windows_manager_impl();

            type_window& create_window();

        private:
            std::map<std::uint32_t, type_window_impl*> windows_map;
        };
    }
}

#endif
