// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/def/abstract_class.h"


namespace engine::platform
{
    abstract_class platform
    {
        abstract_def(platform)

        virtual void* id() = 0;
    };

    extern platform* inst_def;

    void init();
    void term();
}
