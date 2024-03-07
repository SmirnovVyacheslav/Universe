// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/core/api_core.h"

#include "src/core/event/api_event.h"
#include "src/core/control/api_control.h"
#include "src/render/api.h"
#include "src/platform/api/core.h"


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
