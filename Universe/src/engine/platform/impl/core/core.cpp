// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "engine/platform/api/core.h"

#include "engine/platform/api/event.h"
#include "engine/platform/api/view.h"
#include "engine/platform/api/render.h"


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
