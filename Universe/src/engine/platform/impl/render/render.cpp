// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "engine/platform/api/render.h"

#include "engine/platform/impl/render/device.h"


namespace engine::platform::render
{
    void init()
    {
        init_device();
    }

    void term()
    {
        term_device();
    }

    void draw()
    {
        draw_device();
    }
}
