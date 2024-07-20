// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_obj_mesh.h"


#ifndef ENGINE_RENDER_MESH_OBJ
#define ENGINE_RENDER_MESH_OBJ

namespace engine::render::mesh
{
    class obj
    {
        abstract

        virtual void set() = 0;
        virtual int32 size() = 0;
    };
}

#endif
