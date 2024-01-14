// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/type/std.h"


namespace engine::render::settings
{
    struct obj
    {
        int32 width = 128;
        int32 height = 256;
        int32 refresh = 60;

        bool windowed = true;
    };


    void init();
    void term();

    obj& get();
}