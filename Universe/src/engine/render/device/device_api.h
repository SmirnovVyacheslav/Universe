// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "engine/render/model/obj_model.h"
#include "engine/var/string.h"

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
