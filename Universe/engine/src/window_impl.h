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

#include <cstdint>
#include <map>

#include "../include/window.h"


namespace engine
{
    namespace window
    {
        class type_window_impl
        {
        public:
            type_window_impl();
            ~type_window_impl();

            type_window_impl& operator++();
            type_window_impl& operator--();
            std::uint32_t ref_count = 0;
        private:
            //std::uint32_t ref_count = 0;
        };


        class type_window_ui : public type_window
        {
        public:
            type_window_ui(type_window_impl* window_impl);
            ~type_window_ui();
        private:
            type_window_impl* window_impl = nullptr;
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
