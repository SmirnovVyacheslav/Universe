// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/platform/api/render/index_buff.h"
#include "engine/var/map.h"

#include "engine/platform/impl/render/device.h"


namespace engine::platform::render::index_buff
{
    map<int32, index_buff*> index_buff_map;

    void init(string file)
    {
        //
    }

    void init(uint16* data)
    {
        index_buff* new_vindex_buff = render::init_index_buff(data);
        index_buff_map.add(0, new_vindex_buff);
    }

    void term(int32 id)
    {
        delete index_buff_map[id];
    }

    index_buff* get(int32 id)
    {
        return index_buff_map[id];
    }
}
