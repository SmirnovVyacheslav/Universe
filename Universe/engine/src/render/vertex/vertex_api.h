// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/render/vertex/vertex_obj.h"


namespace engine::render::vertex
{
    void init();
    void term();

    obj& get();
}
