// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/platform/api/render.h"

#include "src/platform/impl/render/device.h"
#include "src/platform/impl/render/directx/device_impl.h"


namespace engine::platform::render
{
    device* device_inst = nullptr;


    void init()
    {
        device_inst = new directx::device_impl();
    }

    void term()
    {
        delete device_inst;
    }
}
