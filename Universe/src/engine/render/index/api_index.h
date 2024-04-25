// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "obj_index.h"

#include "engine/var/array.h"
#include "engine/var/std.h"


namespace engine::render::index
{
    void init();

    obj& add(array<uint16> data);

    void term();
}
