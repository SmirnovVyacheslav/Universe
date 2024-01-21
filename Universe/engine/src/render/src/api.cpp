// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/render/inc/api.h"
#include "src/render/src/camera/inc/api.h"
#include "src/render/src/settings/inc/api.h"


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
