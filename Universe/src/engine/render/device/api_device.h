// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "obj_device.h"

#include "engine/render/model/obj_model.h"
#include "engine/render/shader/obj_shader.h"
#include "engine/var/string.h"


namespace engine::render::device
{
    void init();

    void draw(model::obj& model_obj);
    string type();

    void term();
}
