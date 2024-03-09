// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "api_game.h"

#include "core/api_core.h"


namespace game
{
    void init()
    {
        engine::core::init();
    }

    void exec()
    {
        engine::core::exec();
    }

    void term()
    {
        engine::core::term();
    }
}
