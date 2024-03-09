// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "src/render/api_render.h"
#include "src/render/camera/api_camera.h"
#include "src/render/settings/api_settings.h"


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
