// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#include "render.h"
#include "src/platform/api/video/directx/directx.h"

namespace engine
{
    render render::inst = render();


    void render::start_render()
    {
        createDevice();
        createShader();
        setGeometry();
        while (true)
        {
            do_render();
        }
    }
}
