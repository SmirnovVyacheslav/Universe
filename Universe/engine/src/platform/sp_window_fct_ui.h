/******************************************************************************
     * File: src/platform/window_ui.h
     * Description: Platform window implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef PLATFOM_WINDOW_UI_H
#define PLATFOM_WINDOW_UI_H

#include <string>
#include <memory>


namespace engine
{
    namespace platform
    {
        class window_ui
        {
        public:
            virtual ~window_ui() = default;

        protected:
            window_ui() = default;
        };
    }
}

#endif
