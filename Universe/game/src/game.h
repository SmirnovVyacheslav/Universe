// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/def/class_format.h"


namespace game_ui
{
    class game
    {
        ____________________public____________________
        game();
        game(game&& src) = default;
        game(const game & src) = default;

        void run();

        game& operator=(game&& src) = default;
        game& operator=(const game& src) = default;

        ~game();
    };
}
