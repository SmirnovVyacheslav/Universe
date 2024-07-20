// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_api_indices.h"


namespace engine::render::indices
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
