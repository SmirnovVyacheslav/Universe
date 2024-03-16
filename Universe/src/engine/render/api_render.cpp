// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "api_render.h"

#include "camera/api_camera.h"
#include "device/api_device.h"
#include "settings/api_settings.h"


namespace engine::render
{
    void init()
    {
        settings::init();
        camera::init();
        device::init();
    }

    void term()
    {
        camera::term();
        settings::term();
        device::term();
    }
}
