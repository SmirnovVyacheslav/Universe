// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "api_index.h"

#include "directx/impl_index.h"


namespace engine::render::index
{
    obj* inst = nullptr;


    void init()
    {
        term();
    }

    void add(array<uint16> data)
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
