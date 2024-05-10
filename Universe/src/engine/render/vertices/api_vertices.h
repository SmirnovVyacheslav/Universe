// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_h_api_vertices.h"


#ifndef ENGINE_RENDER_VERTICES_API
#define ENGINE_RENDER_VERTICES_API

namespace engine::render::vertices
{
    void init();

    obj& add(array<vertex> data);

    void term();
}

#endif
