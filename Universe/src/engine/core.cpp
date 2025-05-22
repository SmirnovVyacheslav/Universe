// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "core.h"

#include "engine/core/control/api_control.h"
#include "engine/core/event/api_event.h"
#include "engine/core/settings/api_settings.h"
#include "engine/core/view/api_view.h"
#include "engine/render/api_render.h"

namespace engine::core
{
    int run()
    {
        settings::init();
        event::init();
        view::init();
        render::init();

        control::start();

        while (control::status())
        {
            event::handle();
            render::draw();
        }

        render::term();
        view::term();
        event::term();
        settings::term();

        return 0;
    }
}
