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

    obj& add(array<uint16> data)
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
