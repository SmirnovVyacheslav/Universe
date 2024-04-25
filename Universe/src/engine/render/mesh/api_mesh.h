// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "obj_mesh.h"


namespace engine::render::mesh
{
    void init();

    void add(string file);
    obj& get();

    void term();
}
