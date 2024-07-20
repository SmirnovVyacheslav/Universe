// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_api_camera.h"


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
