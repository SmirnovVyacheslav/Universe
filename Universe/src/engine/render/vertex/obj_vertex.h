// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_h_obj_vertex.h"


#ifndef ENGINE_RENDER_VERTEX_OBJ
#define ENGINE_RENDER_VERTEX_OBJ

namespace engine::render::vertex
{
    class obj
    {
        abstract

        int32 id;

        virtual void set() = 0;
    };
}

#endif
