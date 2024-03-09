// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/src/render/vertex/obj_vertex.h"


namespace engine::render::vertex
{
    void init();
    void term();

    obj& get();
}
