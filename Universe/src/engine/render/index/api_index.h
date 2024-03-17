// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "obj_index.h"


namespace engine::render::index
{
    void init();
    void term();

    obj& get();
}
