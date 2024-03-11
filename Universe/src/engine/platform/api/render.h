// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/core/def/abstract_class.h"
#include "engine/var/std.h"
#include "engine/var/string.h"


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
