// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "engine/def/abstract.h"
#include "engine/var/matrix4.h"
#include "engine/var/std.h"


namespace engine::render::shader
{
    class obj
    {
        abstract

        int32 id;

        virtual void set() = 0;
        virtual void update(matrix4 world, matrix4 view, matrix4 projection) = 0;
    };
}
