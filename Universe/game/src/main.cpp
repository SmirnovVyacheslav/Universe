/******************************************************************************
     * File: main.cpp
     * Description: Entry point
     * Created: 07 Oct 2021
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "game.h"


int main(int argc, char* argv[])
{
    /* Game entry point */

    // Create main game instance
    game::t_game game_instance;

    // Run the game
    game_instance.run();

    return 0;
}
