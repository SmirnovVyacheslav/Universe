/******************************************************************************
     * File: game.h
     * Description: Main game interface
     * Created: 07 Oct 2021
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
 */

#pragma once
#ifndef GAME_H
#define GAME_H

#include "../../engine/include/engine.h"


namespace game
{
    /*************************************************************************/
    class t_game
    {
    public:
        t_game();
        ~t_game();

        void run();

    private:
        engine::t_engine engine_instance;
    };
    /*************************************************************************/
}

#endif
