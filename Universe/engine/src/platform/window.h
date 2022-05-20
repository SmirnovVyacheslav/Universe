// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.


#pragma once
#ifndef PLATFOM_WINDOW_UI_H
#define PLATFOM_WINDOW_UI_H

#include "src/core/string.h"


#include <string>
#include <memory>

#include <windows.h>


namespace engine
{
    namespace platform
    {
        class window_impl;

        class window
        {
        public:
            static window inst;

            static void create_window(string name);
            static void* get_handler();

        private:
            window_impl* window_inst;

            window() = default;
            ~window() = default;
        };
    }
}

#endif
