// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/core/def/abstract_class.h"
#include "engine/var/std.h"
#include "engine/var/string.h"
#include "engine/var/vertex.h"


namespace engine::platform::render::vertex_buff
{
    abstract_class vertex_buff
    {
        abstract_def(vertex_buff)

        int32 id;
    };

    void init(string file);
    void init(vertex* data);
    void term(int32 id);

    vertex_buff* get(int32 id);
}
