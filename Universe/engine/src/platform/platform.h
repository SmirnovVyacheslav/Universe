// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/def/abstract.h"


namespace engine::platform
{
    struct api
    {
        abstract_api(api)

        static void initialize();
    };
}
