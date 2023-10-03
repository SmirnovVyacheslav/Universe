// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/type/std.h"
#include "src/core/type/string.h"


namespace engine::platform::window
{
    struct config
    {
        string name = u8"Engine";

        int32 width = 800;
        int32 height = 600;
        int32 refresh_rate = 60;
    };
}
