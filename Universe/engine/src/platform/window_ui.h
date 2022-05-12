/******************************************************************************
     * Description: Platform window ui
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/


#pragma once
#ifndef PLATFOM_WINDOW_UI_H
#define PLATFOM_WINDOW_UI_H


#include <string>
#include <memory>

#include <windows.h>


namespace engine
{
    namespace platform
    {
        class window_obj_ui;
        class window_mng_ui;


        using window_obj_ptr = std::shared_ptr<window_obj_ui>;
        using window_mng_ptr = std::shared_ptr<window_mng_ui>;


        class window_obj_ui
        {
        public:

            virtual ~window_obj_ui() = default;

            virtual HWND get_hwnd() = 0;

        protected:

            window_obj_ui() = default;
        };


        class window_mng_ui
        {
        public:

            static window_mng_ptr create();

            virtual window_obj_ptr create_window(std::wstring name) = 0;

            virtual ~window_mng_ui() = default;

        protected:

            window_mng_ui() = default;
        };
    }
}

#endif
