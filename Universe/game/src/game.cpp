/******************************************************************************
     * File: game.cpp
     * Description: Main game interface
     * Created: 07 Oct 2021
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "game.h"


namespace game
{
    /*************************************************************************/
    t_game::t_game()
    {
        //engine.reset(engine::type_engine::init());
        // Prepare internal data
        // Init engine
    };

    t_game::~t_game()
    {
        // teardown
    }

    void t_game::run()
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
    /*************************************************************************/
}
