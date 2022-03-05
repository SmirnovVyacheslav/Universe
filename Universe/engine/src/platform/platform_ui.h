/******************************************************************************
     * File: src/platform/platform_ui.h
     * Description: Platform UI
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef PLATFORM_UI_H
#define PLATFORM_UI_H

#include <memory>


namespace engine
{
    namespace platform
    {
        class platform_ui
        {
        public:
            static std::shared_ptr<platform_ui> create();
            virtual ~platform_ui();

        protected:
            platform_ui();
        };
    }
}

#endif