// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include "game.h"


namespace game_ui {
    game::game() {
        // Initialize code
    };
    game::~game() {
        // Termination code
    }
    void game::run() {
        engine_inst.initialize_resource();
        // engine_inst.add_object();
        // engine_inst.render();
    };
}
