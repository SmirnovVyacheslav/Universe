// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "api_device.h"


namespace engine::render::device
{
    obj* inst = nullptr;


    void init()
    {
        // inst = new impl;
    }

    void term()
    {
        delete inst;
        inst = nullptr;
    }

    string type()
    {
        return "directx";
    }
}
