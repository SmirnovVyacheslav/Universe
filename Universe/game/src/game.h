// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine_ui.h"


namespace game_ui {
    class game {
        public:
            game();
            ~game();

            void run();
        private:
            engine::ui::engine_ui engine_inst;
    };
}
