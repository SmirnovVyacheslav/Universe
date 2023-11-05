// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "game.h"

#include "src/core/api/core.h"


namespace game_ui
{
    game::game()
    {
        engine::core::init();
    };

    game::~game()
    {
        engine::core::term();
    }

    void game::run()
    {
        engine::core::exec();
    };
}
