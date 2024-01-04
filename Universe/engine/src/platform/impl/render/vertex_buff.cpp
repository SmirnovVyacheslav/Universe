// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/platform/api/render/vertex_buff.h"
#include "src/core/type/map.h"

#include "src/platform/impl/render/device.h"


namespace engine::platform::render::vertex_buff
{
    map<int32, vertex_buff*> vertex_buff_map;

    void init(string file)
    {
        //
    }

    void init(vertex* data)
    {
        vertex_buff* new_vertex_buff = render::init_vertex_buff(data);
        vertex_buff_map.add(0, new_vertex_buff);
    }

    void term(int32 id)
    {
        delete vertex_buff_map[id];
    }

    vertex_buff* get(int32 id)
    {
        return vertex_buff_map[id];
    }
}
