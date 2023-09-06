// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/def/abstract.h"
#include "src/core/data_type/string.h"


namespace engine::platform::window
{
    struct config
    {
        abstract(config)

            string name = u8"Engine";
    };

    config* init();
}
