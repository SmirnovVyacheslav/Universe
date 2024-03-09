// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "obj_camera.h"


namespace engine::render::camera
{
    void init();
    void term();

    obj& get();
}
