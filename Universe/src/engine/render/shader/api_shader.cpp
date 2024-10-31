// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_api_shader.h"


namespace engine::render::shader
{
    obj* inst = nullptr;


    void init()
    {
        term();
    }

    obj& add(string file)
    {
        inst = new directx::impl(file);
        return *inst;
    }

    void term()
    {
        delete inst;
        inst = nullptr;
    }
}
