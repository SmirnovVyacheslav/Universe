/******************************************************************************
     * File: src/platform/windows/platform_impl.h
     * Description: Platform UI implementation
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "src/platform/macros_def.h"

#pragma once
#ifdef PLATFORM_WINDOWS
#ifndef PLATFORM_IMLP_H
#define PLATFORM_IMLP_H

#include <memory>
#include <string>

#include "src/platform/platform_ui.h"
#include "src/platform/windows/window_impl/window_data.h"
#include "src/platform/windows/window_impl/window_impl.h"


namespace engine
{
    namespace platform
    {
        class platform_impl: public platform_ui
        {
        public:
            platform_impl();
            ~platform_impl();

            std::shared_ptr<window_ui> create_window(std::wstring name);

        private:
            std::shared_ptr<window_data> window_data_instance;
        };
    }
}

#endif
#endif
