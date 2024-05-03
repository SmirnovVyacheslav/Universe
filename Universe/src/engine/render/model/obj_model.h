// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "engine/def/abstract.h"

#include "engine/var/std.h"


#ifndef ENGINE_RENDER_MODEL_OBJ
#define ENGINE_RENDER_MODEL_OBJ

namespace engine::render::model
{
    class obj
    {
        abstract

        virtual void set() = 0;
        virtual int32 size() = 0;
    };
}

#endif
