/******************************************************************************
     * File: game.cpp
     * Description: Main game interface
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "game.h"


namespace game
{
    type_game::type_game() : engine_instance(engine::type_engine::initialize())
    {
        // Initialize code
    };
    type_game::~type_game()
    {
        engine_instance.terminate();
    }
    void type_game::run()
    {
        // Run code
        engine::window::type_window& window_instance = engine_instance.windows_manager.create_window();
    };
}
