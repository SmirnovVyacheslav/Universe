// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_obj_camera.h"


#ifndef ENGINE_RENDER_CAMERA_OBJ
#define ENGINE_RENDER_CAMERA_OBJ

namespace engine::render::camera
{
    class obj
    {
        abstract

        virtual matrix4 world() = 0;
        virtual matrix4 view() = 0;
        virtual matrix4 projection() = 0;
    };
}

#endif
