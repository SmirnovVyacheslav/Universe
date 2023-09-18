// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/def/abstract_class.h"
#include "src/platform/window/config.h"


namespace engine::platform::window
{
    abstract_class window
    {
        abstract_def(window)

        virtual void* id() = 0;
    };

    window* init(config* cfg);
}
