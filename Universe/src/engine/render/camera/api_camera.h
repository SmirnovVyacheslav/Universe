// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_h_api_camera.h"


#ifndef ENGINE_RENDER_CAMERA_API
#define ENGINE_RENDER_CAMERA_API

namespace engine::render::camera
{
    void init();

    obj& get();

    void term();
}

#endif
