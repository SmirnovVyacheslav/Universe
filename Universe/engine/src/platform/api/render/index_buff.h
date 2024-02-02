// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/def/abstract_class.h"
#include "src/var/std.h"
#include "src/var/string.h"


namespace engine::platform::render::index_buff
{
    abstract_class index_buff
    {
        abstract_def(index_buff)

        int32 id;
    };

    void init(string file);
    void init(uint16* data);
    void term(int32 id);

    index_buff* get(int32 id);
}
