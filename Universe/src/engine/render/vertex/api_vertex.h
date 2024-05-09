// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_h_api_vertex.h"


#ifndef ENGINE_RENDER_VERTEX_API
#define ENGINE_RENDER_VERTEX_API

namespace engine::render::vertex
{
    void init();

    obj& add(array<engine::vertex> data);

    void term();
}

#endif
