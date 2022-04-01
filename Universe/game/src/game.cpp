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
    type_game::type_game() : engine_instance(engine::engine_mng_ui::create())
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
        engine_instance->window_mng->create_window(L"Main");
    };
}
