// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_api_render.h"


#ifndef ENGINE_RENDER_API
#define ENGINE_RENDER_API

namespace engine::render
{
    void init();

    void draw();

    void term();
}

#endif
