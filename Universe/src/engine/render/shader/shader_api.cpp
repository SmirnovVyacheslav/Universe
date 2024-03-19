// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "shader_api.h"


namespace engine::render::shader
{
    obj* inst = nullptr;


    void init()
    {
        //inst = new obj;
    }

    obj& get()
    {
        return *inst;
    }

    void term()
    {
        // delete inst;
        // inst = nullptr;
    }
}
