// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include "game.h"
#include "src/gsi/gsi.h"


namespace game_ui {
    game::game() {
        // Initialize code
        engine::gsi::smf_c_gsi();
    };
    game::~game() {
        // Termination code
        engine::gsi::smf_d_gsi();
    }
    void game::run() {
        // engine_inst.initialize_resource();
    };
}
