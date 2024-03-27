// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "shader_api.h"

#include "directx/shader_impl.h"


namespace engine::render::shader
{
    obj* inst = nullptr;


    void init()
    {
        inst = new directx::impl("res/game/shader/base.fx");
    }

    obj& get()
    {
        return *inst;
    }

    void term()
    {
        delete inst;
        inst = nullptr;
    }
}
