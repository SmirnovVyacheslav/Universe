// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_obj_shader.h"


#ifndef ENGINE_RENDER_SHADER_OBJ
#define ENGINE_RENDER_SHADER_OBJ

namespace engine::render::shader
{
    class obj
    {
        abstract

        int32 id;

        virtual void set() = 0;
    };
}

#endif
