/******************************************************************************
     * File: window_impl.cpp
     * Description: Windows implementation
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "window_impl.h"


namespace engine
{
    namespace window
    {
        type_window_impl::type_window_impl()
        {
            // Initialize code
        }
        type_window_impl::~type_window_impl()
        {
            // Terminate code
        }
        type_window_impl& type_window_impl::operator++()
        {
            ref_count++;
            return *this;
        }
        type_window_impl& type_window_impl::operator--()
        {
            ref_count--;
            if (ref_count == 0)
            {
                delete this;
            }
            return *this;
        }


        type_window_ui::type_window_ui(type_window_impl* window_impl) : window_impl(window_impl)
        {
            //++(this->window_impl);
            this->window_impl->ref_count++;
        }
        type_window_ui::~type_window_ui()
        {
            //--(this->window_impl);
            this->window_impl->ref_count--;
        }


        type_windows_manager_impl::type_windows_manager_impl()
        {
            // Initialize code
        }
        type_windows_manager_impl::~type_windows_manager_impl()
        {
            // Terminate code
        }
        type_window& type_windows_manager_impl::create_window()
        {
            type_window_impl* new_window = new type_window_impl;
            windows_map[1] = new_window;
            type_window* new_window_ui = new type_window_ui(new_window);
            return *new_window_ui;
        }
    }
}
