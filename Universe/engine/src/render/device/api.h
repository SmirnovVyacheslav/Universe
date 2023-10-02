// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/def/abstract_class.h"
#include "src/render/device/cfg.h"


namespace engine::render::device
{
    struct api_t
    {
        abstract_def(api_t)

        static api_t* initialize(const cfg_t* cfg);
    };
}
