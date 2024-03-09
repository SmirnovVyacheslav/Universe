// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "api_core.h"

#include "render/api_render.h"

#include "platform/api/core.h"

#include "event/api_event.h"
#include "control/api_control.h"


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
