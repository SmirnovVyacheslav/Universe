// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "engine/def/abstract.h"
#include "engine/var/std.h"
#include "engine/var/string.h"
#include "engine/var/vector3.h"

#ifndef ENGINE_RENDER_TEXT_OBJ
#define ENGINE_RENDER_TEXT_OBJ

namespace engine::render::text
{
    class obj
    {
        abstract

        int32 id = 0;
        string text = u8"Hello";
        vector3 color = { 0.0f, 1.0f, 0.0f };

        virtual void set() = 0;
    };
}

#endif
