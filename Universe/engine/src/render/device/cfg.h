// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/data_type/std.h"


namespace engine::render::device
{
    struct cfg_t
    {
        int_32 width = 128;
        int_32 height = 256;
        int_32 refresh = 60;

        bool windowed = true;

        void* window_handler;
    };
}
