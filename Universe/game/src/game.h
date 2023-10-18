// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
// engine
#include "engine_ui.h"

#define ____________________public____________________ public:
#define ____________________private___________________ private:
#define ____________________protected_________________ protected:
#define ____________________define____________________
#define ____________________friend____________________


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
        ____________________private___________________
        engine::ui::engine_ui engine_inst;
    };
}
