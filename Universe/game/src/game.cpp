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
    type_game::type_game() : engine_instance(engine::engine_ui::create())
    {
        // Initialize code
    };
    type_game::~type_game()
    {
        //ff
    }
    void type_game::run()
    {
        // Run code
        //engine::window::type_window& window_instance = engine_instance.windows_manager.create_window();
        engine_instance->create_window(L"Main");
    };
}
