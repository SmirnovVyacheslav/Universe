// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/render/api.h"
#include "src/render/camera/api.h"
#include "src/render/settings/api.h"


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
