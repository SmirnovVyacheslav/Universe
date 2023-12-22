// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/platform/api/render/shader.h"
#include "src/core/type/map.h"


namespace engine::platform::render::shader
{
    map<int32, shader*> shader_map;

    void init(string file)
    {
        //
    }

    void term(int32 id)
    {
        //
    }

    void get(int32 id)
    {
        //
    }
}
