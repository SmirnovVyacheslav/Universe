// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "obj_model.h"
#include "engine/render/model/obj_model.h"

#include "engine/var/string.h"


#ifndef ENGINE_RENDER_MODEL_API
#define ENGINE_RENDER_MODEL_API

namespace engine::render::model
{
    void init();

    obj& add(string name);

    void term();
}

#endif
