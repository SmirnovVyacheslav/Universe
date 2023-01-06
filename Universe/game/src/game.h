// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine_ui.h"


namespace game_ui {
    class game {
    public:
        game();
        game(game&& src) = default;
        game(const game & src) = default;

        void run();

        game& operator=(game&& src) = default;
        game& operator=(const game& src) = default;

        ~game();
    private:
        engine::ui::engine_ui engine_inst;
    };
}
