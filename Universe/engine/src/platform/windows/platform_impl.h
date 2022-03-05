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

#include "src/platform/platform_ui.h"


namespace engine
{
    namespace platform
    {
        class platform_impl: public platform_ui
        {
        public:
            platform_impl();
            ~platform_impl();

        private:
            //gg
        };
    }
}

#endif
#endif
