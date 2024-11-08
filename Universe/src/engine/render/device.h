// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "engine/def/abstract.h"

#ifndef ENGINE_RENDER_DEVICE
#define ENGINE_RENDER_DEVICE

namespace engine::render::device
{
    #define render_device_api

    class obj
    {
        abstract

        render_device_api
    };


    obj& add();

    obj& get();

    void del();
}

#endif
