// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "engine.h"

#include "engine/core/api_core.h"

namespace engine
{
    int run()
    {
        engine::core::init();
        engine::core::exec();
        engine::core::term();

        return 0;
    }
}
