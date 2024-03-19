// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "shader_obj.h"


namespace engine::render::shader
{
    void init();

    obj& get();

    void term();
}
