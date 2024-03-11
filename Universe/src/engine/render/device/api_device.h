// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "engine/def/abstract.h"
#include "engine/var/string.h"


namespace engine::render::device
{
    class obj
    {
        abstract

        virtual void draw() = 0;
    };


    void init();
    void term();

    string type();
}
