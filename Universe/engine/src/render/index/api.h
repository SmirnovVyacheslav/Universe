// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/render/src/index/inc/obj.h"


namespace engine::render::index
{
    void init();
    void term();

    obj& get();
}
