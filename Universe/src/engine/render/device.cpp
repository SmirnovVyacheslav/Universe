// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "device.h"

#include "engine/sdk/directx/device.h"

namespace engine::render::device
{
    obj* inst = nullptr;

    
    obj& add()
    {
        return *inst;
    }

    obj& get()
    {
        return *inst;
    }

    void del()
    {
        delete inst;
    }
}
