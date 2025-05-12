// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "game.h"

#include "engine/core/api_core.h"

namespace game
{
    int run()
    {
        engine::core::init();
        engine::core::exec();
        engine::core::term();

        return 0;
    }
}
