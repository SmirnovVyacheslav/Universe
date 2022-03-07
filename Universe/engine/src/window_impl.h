/******************************************************************************
     * File: src/window_impl.h
     * Description: Windows implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef WINDOW_IMPL_H
#define WINDOW_IMPL_H

//#include <map>
#include <memory>
#include <string>

#include "window_ui.h"
#include "src/platform/platform_ui.h"
#include "src/platform/window_ui.h"


namespace engine
{
    namespace window
    {
        class window_impl: public window_ui
        {
        public:
            window_impl(std::shared_ptr<platform::platform_ui> platform_instance, std::wstring name);
            ~window_impl();
        private:
            std::wstring name;
            std::shared_ptr<platform::window_ui> window_instance;
        };


        /*class type_windows_manager_impl : public type_windows_manager
        {
        public:
            type_windows_manager_impl();
            ~type_windows_manager_impl();

            type_window& create_window();

        private:
            std::map<std::uint32_t, type_window_impl*> windows_map;
        };*/
    }
}

#endif
