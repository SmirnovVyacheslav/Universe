/******************************************************************************
     * File: main.cpp
     * Description: Entry point
     * Copyright: (C) 2021 Vyacheslav Smirnov, All rights reserved.
     * Author: Vyacheslav Smirnov
     * Email: necrolazy@gmail.com
******************************************************************************/

#include "game.h"


int main(int argc, char* argv[])
{
    // Game entry point
    game::type_game game_instance;

    game_instance.run();

    return 0;
}
