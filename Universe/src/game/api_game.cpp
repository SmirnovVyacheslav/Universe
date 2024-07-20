// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_api_game.h"


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
