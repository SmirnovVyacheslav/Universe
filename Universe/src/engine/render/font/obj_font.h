// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_obj_font.h"


#ifndef ENGINE_RENDER_FONT_OBJ
#define ENGINE_RENDER_FONT_OBJ

namespace engine::render::font
{
    class obj
    {
        abstract

        int32 id;

        virtual void set() = 0;
    };
}

#endif
