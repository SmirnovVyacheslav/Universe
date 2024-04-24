// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "api_vertex.h"

#include "directx/impl_vertex.h"


namespace engine::render::vertex
{
    obj* inst = nullptr;


    void init()
    {
        term();
    }

    void add(array<engine::vertex> data)
    {
        inst = new directx::impl(data);
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
