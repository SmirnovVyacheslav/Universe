// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/platform/api/render/shader.h"
#include "src/core/type/map.h"

#include "src/platform/impl/render/device.h"


namespace engine::platform::render::shader
{
    map<int32, shader*> shader_map;

    void init(string file)
    {
        shader* new_shader = render::init_shader(file);
        shader_map.add(0, new_shader);
    }

    void term(int32 id)
    {
        delete shader_map[id];
    }

    shader* get(int32 id)
    {
        return shader_map[id];
    }
}
