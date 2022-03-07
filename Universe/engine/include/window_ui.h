/******************************************************************************
     * File: window_ui.h
     * Description: API to work with windows
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef WINDOW_UI_H
#define WINDOW_UI_H


namespace engine
{
    namespace window
    {
        class window_ui
        {
        public:
            virtual ~window_ui() = default;
        protected:
            window_ui() = default;
        };


        /*class windows_manager_ui
        {
        public:
            virtual type_window& create_window() = 0;
        protected:
            type_windows_manager() = default;
            virtual ~type_windows_manager() = default;
        };*/
    }
}

#endif
