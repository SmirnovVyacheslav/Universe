// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_s_api_camera.h"


namespace engine::render::camera
{
    obj* inst = nullptr;


    void init()
    {
        term();
        inst = new impl();
    }

    obj& get()
    {
        return *inst;
    }

    void term()
    {
        delete inst;
        inst = nullptr;
    }
}
