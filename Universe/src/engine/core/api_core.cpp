// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "api_core.h"

#include "event/api_event.h"
#include "control/api_control.h"

#include "engine/render/api_render.h"
#include "engine/platform/api/core.h"


namespace engine::core
{
    void init()
    {
        platform::init();
        render::init();
    }

    void exec()
    {
        control::start();

        while (control::status())
        {
            event::handle();
        }
    }

    void term()
    {
        render::term();
        platform::term();
    }
}
