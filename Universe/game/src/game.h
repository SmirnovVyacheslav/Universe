/******************************************************************************
     * File: game.h
     * Description: Main game interface
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

/* ***************************************************************************
 * Name convention
 * ***************************************************************************
 * type_name   = data type / class
 * const_name  = global constant
 * global_name = global variable
 * this.name   = data type member
 * interface   = interface
 */

#pragma once
#ifndef GAME_H
#define GAME_H

#include <memory>

#include "engine_ui.h"


namespace game
{
    // Interface
    class type_game
    {
    public:
        type_game();
        ~type_game();

        void run();

    private:
        std::shared_ptr<engine::engine_ui> engine_instance;
    };
}

#endif
