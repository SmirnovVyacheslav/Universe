/******************************************************************************
     * Description: Platform ui
     * Copyright: (C) 2022 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/


#pragma once
#ifndef PLATFORM_UI_H
#define PLATFORM_UI_H


#include "src/platform/window_ui.h"


namespace engine
{
    namespace platform
    {
        class platform_mng_ui;


        using platform_mng_ptr = std::shared_ptr<platform_mng_ui>;


        class platform_mng_ui
        {
        public:

            const window_mng_ptr window_mng;


            static platform_mng_ptr create();

            virtual ~platform_mng_ui() = default;

        protected:

            platform_mng_ui();
        };
    }
}

#endif