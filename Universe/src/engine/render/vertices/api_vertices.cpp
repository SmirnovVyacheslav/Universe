// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_api_vertices.h"


namespace engine::render::vertices
{
    obj* inst = nullptr;


    void init()
    {
        term();
    }

    obj& add(array<engine::vertex> data)
    {
        inst = new directx::impl(data);
        return *inst;
    }

    void term()
    {
        delete inst;
        inst = nullptr;
    }
}
