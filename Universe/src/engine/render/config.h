// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "engine/lib/ref.h"

#ifndef ENGINE_RENDER_CONFIG
#define ENGINE_RENDER_CONFIG

namespace engine::render::config
{
    class obj
    {
    public:
        ref<int> width;
        ref<int> height;
        ref<int> refresh;

        obj() = default;
        ~obj() = default;

        obj(obj&& src) = delete;
        obj(const obj& src) = delete;

        obj& operator=(obj&& src) = delete;
        obj& operator=(const obj& src) = delete;
    };
}

#endif
