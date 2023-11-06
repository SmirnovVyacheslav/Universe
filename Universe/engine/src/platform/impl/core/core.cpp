// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/platform/api/core.h"

#include "src/platform/api/event.h"
#include "src/platform/api/view.h"
#include "src/platform/api/render.h"


namespace engine::platform
{
    void init()
    {
        event::init();
        view::init();
        render::init();
    }

    void term()
    {
        render::term();
        view::term();
        event::term();
    }
}
