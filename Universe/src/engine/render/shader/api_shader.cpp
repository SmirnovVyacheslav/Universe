// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_api_shader.h"


namespace engine::render::shader
{
    obj* inst = nullptr;


    void init()
    {
        term();
    }

    obj& add(string name)
    {
        inst = new directx::impl(name);
        return *inst;
    }

    void term()
    {
        delete inst;
        inst = nullptr;
    }
}
