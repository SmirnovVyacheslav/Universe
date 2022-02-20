/******************************************************************************
     * File: platform.platform_api.cpp
     * Description: Platform API
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "../macros.h"
#include "../platform_api.h"

#ifdef PLATFORM_WINDOWS


namespace engine
{
    namespace platform
    {
        class platform_api::platform_data
        {
        public:
            platform_data();
            ~platform_data();
        };


        platform_api::platform_api()
        {

        }

        platform_api::~platform_api()
        {

        }



    }
}

#endif
