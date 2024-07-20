// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_api_mesh.h"


#ifndef ENGINE_RENDER_MESH_API
#define ENGINE_RENDER_MESH_API

namespace engine::render::mesh
{
    void init();

    obj& add(string file);

    void term();
}

#endif
