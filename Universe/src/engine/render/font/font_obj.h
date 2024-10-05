// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "engine/def/abstract.h"
#include "engine/var/std.h"

#ifndef ENGINE_RENDER_FONT_OBJ
#define ENGINE_RENDER_FONT_OBJ

namespace engine::render::font
{
    class obj
    {
        abstract

        int32 id = 0;

        virtual void set() = 0;
    };
}

#endif
