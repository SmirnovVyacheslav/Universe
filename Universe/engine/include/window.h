/******************************************************************************
     * File: window.h
     * Description: API to work with windows
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef WINDOW_H
#define WINDOW_H


namespace engine
{
    namespace window
    {
        // Interface
        class type_window
        {
        public:
            virtual ~type_window() = default;
        protected:
            type_window() = default;
        };


        // Interface
        class type_windows_manager
        {
        public:
            virtual type_window& create_window() = 0;
        protected:
            type_windows_manager() = default;
            virtual ~type_windows_manager() = default;
        };
    }
}

#endif
