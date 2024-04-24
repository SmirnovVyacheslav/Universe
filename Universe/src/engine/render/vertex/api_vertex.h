// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "obj_vertex.h"

#include "engine/var/array.h"
#include "engine/var/vertex.h"


namespace engine::render::vertex
{
    void init();

    void add(array<engine::vertex> data);
    obj& get();

    void term();
}
