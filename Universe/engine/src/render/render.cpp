// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#include "render.h"
#include "src/platform/api/video/directx/directx.h"

namespace engine
{
    render render::inst = render();


    void render::start_render()
    {
        directx directx_api;
        directx_api.create_device();
        /*createDevice();
        createShader();
        setGeometry();
        while (true)
        {
            do_render();
        }*/
    }
}
