// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/render/device/api.h"


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
}
