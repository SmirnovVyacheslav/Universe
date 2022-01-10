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
 * t_name = data type / class
 * c_name = global constant
 * g_name = global variable
 * m_name = data type member
 * 
 * type_name = data type / class
 * const_name = global constant
 * global_name = global variable
 * this.name = data type member
 * interface = interface
 */

#pragma once
#ifndef GAME_H
#define GAME_H

#include "../../engine/include/engine.h"


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
        engine::type_engine& engine_instance;
    };
}

#endif
