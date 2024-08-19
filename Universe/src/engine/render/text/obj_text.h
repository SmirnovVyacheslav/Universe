// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_obj_text.h"


#ifndef ENGINE_RENDER_TEXT_OBJ
#define ENGINE_RENDER_TEXT_OBJ

namespace engine::render::text
{
    class obj
    {
        abstract

        int32 id;
        string text;
        vector3 color;

        virtual void set() = 0;
    };
}

#endif
