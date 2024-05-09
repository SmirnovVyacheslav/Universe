// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "engine/def/abstract.h"

#include "engine/render/model/obj_model.h"
#include "engine/render/shader/obj_shader.h"


namespace engine::render::device
{
    class obj
    {
        abstract

        virtual void draw(model::obj& model_obj) = 0;
    };
}
