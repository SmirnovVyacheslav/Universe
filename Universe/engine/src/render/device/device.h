// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/definition.h"
#include "src/render/device/cfg.h"


namespace engine::render::device
{
    struct device_t
    {
        abstract(device_t)

        static device_t* initialize(const cfg_t& cfg);
    };
}
