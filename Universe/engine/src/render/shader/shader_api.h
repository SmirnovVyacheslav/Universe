// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/render/shader/shader_obj.h"


namespace engine::render::shader
{
    void init();
    void term();

    obj& get();
}
