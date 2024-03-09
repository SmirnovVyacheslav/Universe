// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "engine/src/platform/api/core.h"

#include "engine/src/platform/api/event.h"
#include "engine/src/platform/api/view.h"
#include "engine/src/platform/api/render.h"


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
