// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_obj_device.h"


#ifndef ENGINE_RENDER_DEVICE_OBJ
#define ENGINE_RENDER_DEVICE_OBJ

namespace engine::render::device
{
    class obj
    {
        abstract

        virtual void draw(model::obj& model_obj) = 0;
    };
}

#endif
