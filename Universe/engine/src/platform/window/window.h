// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/def/abstract.h"
#include "src/platform/window/config.h"


namespace engine::platform::window
{
    struct window
    {
        abstract(window)

        virtual void* id();
    };

    window* init(config* cfg);
}
