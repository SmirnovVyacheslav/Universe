// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef GAME_H
#define GAME_H

#include "engine_ui.h"


namespace game
{
    class game
    {
    public:
        game();
        ~game();

        void run();

    private:
        engine_ui::engine engine_inst;
    };
}
#endif
