// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/core/api/core.h"

#include "src/core/api/control.h"
#include "src/core/api/event.h"
#include "src/platform/api/core.h"
#include "src/platform/api/render.h"


namespace engine::core
{
    void init()
    {
        platform::init();
        //platform::render::init_shader("game/res/shader/base.fx");
    }

    void exec()
    {
        control::start();

        while (control::status())
        {
            event::handle();
            platform::render::draw();
        }
    }

    void term()
    {
        platform::term();
    }
}
