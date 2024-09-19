// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_api_font.h"


#ifndef ENGINE_RENDER_FONT_API
#define ENGINE_RENDER_FONT_API

namespace engine::render::font
{
    void init();

    obj& get(string name);

    void term();
}

#endif
