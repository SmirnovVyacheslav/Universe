// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "engine/platform/api/core.h"

#include "engine/platform/api/view.h"


namespace engine::platform
{
    void init()
    {
        view::init();
    }

    void term()
    {
        view::term();
    }
}
