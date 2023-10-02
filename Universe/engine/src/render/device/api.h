// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/definition.h"
#include "src/render/device/cfg.h"


namespace engine::render::device
{
    struct api_t
    {
        abstract(api_t)

        static api_t* initialize(const cfg_t* cfg);
    };
}
