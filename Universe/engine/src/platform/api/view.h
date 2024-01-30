// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/var/std.h"
#include "src/core/type/string.h"


namespace engine::platform::view
{
    struct view_config
    {
        string name = u8"Engine";

        int32 width = 128;
        int32 height = 256;
        int32 refresh_rate = 60;
    };


    void init();
    void term();

    void* id();
}
