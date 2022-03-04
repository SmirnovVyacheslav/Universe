/******************************************************************************
     * File: platform.platform_api.h
     * Description: Platform API
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef PLATFORM_PLATFORM_API_H
#define PLATFORM_PLATFORM_API_H

#include <memory>


namespace engine
{
    namespace platform
    {
        class platform_data;

        class platform_api
        {
        public:
            platform_api();
            ~platform_api();

        private:
            std::shared_ptr<platform_data> data;
        };
    }
}

#endif