/******************************************************************************
     * Description: Platform window implementation ui
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/


#include "src/platform/platform_def.h"


#pragma once
#ifdef WINDOWS
#ifndef PLATFORM_WINDOW_IMPL_H
#define PLATFORM_WINDOW_IMPL_H


#include <windows.h>
#include "window_handler.h"
#include "window_descriptor.h"
#include "src/platform/window_ui.h"


namespace engine
{
    namespace platform
    {
        class window_obj_impl;
        class window_mng_impl;


        class window_obj_impl : public window_obj_ui
        {
        public:

            window_obj_impl(std::wstring window_name, window_descriptor window_descriptor);

            ~window_obj_impl();

        private:

            std::wstring name;

            HWND id;
        };


        class window_mng_impl : public window_mng_ui
        {
        public:

            window_mng_impl();

            ~window_mng_impl();

            std::wstring default_descriptor_name();

            window_obj_ptr create_window(std::wstring name);

        private:

            window_descriptor default_descriptor;
        };
    }
}

#endif
#endif
