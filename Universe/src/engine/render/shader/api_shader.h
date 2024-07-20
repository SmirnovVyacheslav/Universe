// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_api_shader.h"


#ifndef ENGINE_RENDER_SHADER_API
#define ENGINE_RENDER_SHADER_API

namespace engine::render::shader
{
    void init();

    obj& add(string name);

    void term();
}

#endif
