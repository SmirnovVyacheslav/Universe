// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/def/abstract_class.h"


namespace engine::render
{
    struct api_t
    {
        abstract_def(api_t)

        static void initialize();
    };
}
