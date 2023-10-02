// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/data_type/std.h"
#include "src/core/data_type/string.h"


namespace engine::platform::window
{
    struct config
    {
        string name = u8"Engine";

        int_32 width = 800;
        int_32 height = 600;
        int_32 refresh_rate = 60;
    };
}
