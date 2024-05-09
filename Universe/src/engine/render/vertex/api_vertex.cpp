// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_s_api_vertex.h"


namespace engine::render::vertex
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
