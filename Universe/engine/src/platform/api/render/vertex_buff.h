// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/def/abstract_class.h"
#include "src/core/type/std.h"
#include "src/core/type/string.h"
#include "src/core/type/vertex.h"


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
