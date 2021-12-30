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
    type_game::type_game()
    {
        // Init
    };
    type_game::~type_game()
    {
        // Teardown
    }
    void type_game::run()
    {
        // abstraction - platform

        // properties
        // devices
        // windows
        // system_events

        // w = create_window(name, settings)
        // struct window_settings - init manually, from config, from default settings (min, max)
        // w.init_from_default(max, min settings)
        // w.init_from_config()
        // w.set_resolution()
        // w.set_mode()
        // w.set_monitor()
        // w.show_window()
        // destroy_window(w)
    };
}
