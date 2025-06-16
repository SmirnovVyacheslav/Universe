// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "engine/def/obj.h"
#include "engine/lib/ref.h"

#ifndef ENGINE_RENDER_CONFIG
#define ENGINE_RENDER_CONFIG

namespace engine::render::config
{
    class obj
    {
        obj_def

        ref<int> width;
        ref<int> height;

        ref<int> refresh;
    };
}

#endif
