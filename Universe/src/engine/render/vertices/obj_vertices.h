// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_obj_vertices.h"


#ifndef ENGINE_RENDER_VERTICES_OBJ
#define ENGINE_RENDER_VERTICES_OBJ

namespace engine::render::vertices
{
    class obj
    {
        abstract

        int32 id;

        virtual void set() = 0;
    };
}

#endif
