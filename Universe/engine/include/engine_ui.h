/******************************************************************************
     * Description: Engine ui
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#pragma once
#ifndef ENGINE_UI_H
#define ENGINE_UI_H

#include "window_ui.h"


namespace engine
{
    class engine_mng_ui;
    using engine_mng_ptr = std::shared_ptr<engine_mng_ui>;


    class engine_mng_ui
    {
    public:
        const window_mng_ptr window_mng;

        static engine_mng_ptr create();

    protected:
        engine_mng_ui() = default;
        virtual ~engine_mng_ui() = default;
    };
}
#endif
