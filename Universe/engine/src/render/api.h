// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/definition.h"


namespace engine::render
{
    struct api_t
    {
        abstract(api_t)

        static void initialize();
    };
}
