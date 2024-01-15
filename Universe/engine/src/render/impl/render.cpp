// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/render/api/render.h"

#include "src/render/api/camera.h"
#include "src/render/api/settings.h"


namespace engine::render
{
    void init()
    {
        settings::init();
        camera::init();
    }

    void term()
    {
        camera::term();
        settings::term();
    }
}
