// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/core/api/core.h"

#include "src/core/api/control.h"
#include "src/core/api/event.h"
#include "src/core/type/std.h"
#include "src/core/type/vertex.h"
#include "src/platform/api/core.h"
#include "src/platform/api/render.h"
#include "src/platform/api/render/shader.h"
#include "src/platform/api/render/vertex_buff.h"
#include "src/platform/api/render/index_buff.h"


namespace engine::core
{
    void init()
    {
        platform::init();

        platform::render::shader::init("game/res/shader/base.fx");
        //platform::render::vertex_buff::init();
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
