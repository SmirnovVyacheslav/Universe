// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "obj_shader.h"

#include "engine/var/string.h"


namespace engine::render::shader
{
    void init();

    obj& add(string file);

    void term();
}
