// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "game/api_game.h"


int main(int argc, char* argv[])
{
    game::init();

    game::exec();

    game::term();

    return 0;
}
