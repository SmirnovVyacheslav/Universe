// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_obj_indices.h"


#ifndef ENGINE_RENDER_INDICES_OBJ
#define ENGINE_RENDER_INDICES_OBJ

namespace engine::render::indices
{
    class obj
    {
        abstract

        int32 id;

        virtual void set() = 0;
        virtual int32 size() = 0;
    };
}

#endif
