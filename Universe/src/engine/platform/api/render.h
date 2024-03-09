// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/src/core/def/abstract_class.h"
#include "engine/src/var/std.h"
#include "engine/src/var/string.h"


namespace engine::platform::render
{
    struct render_config
    {
        int32 width = 128;
        int32 height = 256;
        int32 refresh = 60;

        bool windowed = true;
    };

    void init();
    void term();

    void draw();
}
