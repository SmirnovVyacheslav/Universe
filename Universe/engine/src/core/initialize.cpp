// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/core/initialize.h"

#include "src/platform/api/core.h"


namespace engine
{
    void initialize()
    {
        platform::init();
    }

    void terminate()
    {
        platform::term();
    }
}
