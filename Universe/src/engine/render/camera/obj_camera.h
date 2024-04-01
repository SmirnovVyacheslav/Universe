// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "engine/def/abstract.h"
#include "engine/var/matrix4.h"


namespace engine::render::camera
{
    class obj
    {
        abstract

        virtual matrix4 world() = 0;
        virtual matrix4 view() = 0;
        virtual matrix4 projection() = 0;
    };
}
