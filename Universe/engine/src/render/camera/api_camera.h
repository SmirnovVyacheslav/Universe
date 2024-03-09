// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/render/camera/obj_camera.h"


namespace engine::render::camera
{
    void init();
    void term();

    obj& get();
}
