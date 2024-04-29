// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "engine/def/abstract.h"
#include "engine/var/std.h"


namespace engine::render::index
{
    class obj
    {
        abstract

        int32 id;

        virtual void set() = 0;
        virtual int32 size() = 0;
    };
}
