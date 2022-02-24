/******************************************************************************
     * File: platform.windows.platform_data.h
     * Description: Platform data
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "../macros.h"

#pragma once
#ifdef PLATFORM_WINDOWS
#ifndef PLATFORM_PLATFORM_DATA_H
#define PLATFORM_PLATFORM_DATA_H

#include <memory>


namespace engine
{
    namespace platform
    {
        class platform_data
        {
        public:
            platform_data();
            ~platform_data();

        private:
        };
    }
}

#endif
#endif
