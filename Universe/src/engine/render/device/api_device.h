// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_h_api_device.h"


#ifndef ENGINE_RENDER_DEVICE_API
#define ENGINE_RENDER_DEVICE_API

namespace engine::render::device
{
    void init();

    void draw(model::obj& model_obj);
    string type();

    void term();
}

#endif
