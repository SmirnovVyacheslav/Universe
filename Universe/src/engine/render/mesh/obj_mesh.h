// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "engine/def/abstract.h"
#include "engine/var/string.h"


namespace engine::render::mesh
{
    class obj
    {
        abstract

        virtual void init(string file) = 0;
        virtual void set() = 0;
    };
}
