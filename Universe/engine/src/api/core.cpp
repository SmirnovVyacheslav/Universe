// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/api/core.h"

#include "src/platform/api/core.h"


namespace engine
{
    void init()
    {
        platform::init();
    }

    void exec()
    {
        //
    }

    void term()
    {
        platform::term();
    }
}
