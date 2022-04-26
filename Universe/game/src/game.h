// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef GAME_H
#define GAME_H

#include "engine_ui.h"


namespace game_ui
{
    class game
    {
    public:
        game();
        ~game();

        void run();

    private:
        engine::ui::engine_ui engine_inst;
    };
}
#endif
