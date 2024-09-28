// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_impl_font.h"


#ifndef ENGINE_RENDER_FONT_IMPL
#define ENGINE_RENDER_FONT_IMPL

namespace engine::render::font
{
    class impl : public obj
    {
        uint16 tex_width = 0;
        uint16 tex_height = 0;

        impl(string name);
    };
}

#endif
