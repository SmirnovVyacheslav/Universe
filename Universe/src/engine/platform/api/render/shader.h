// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/src/core/def/abstract_class.h"
#include "engine/src/var/std.h"
#include "engine/src/var/string.h"


namespace engine::platform::render::shader
{
    abstract_class shader
    {
        abstract_def(shader)

        int32 id;
    };

    void init(string file);
    void term(int32 id);

    shader* get(int32 id);
}
