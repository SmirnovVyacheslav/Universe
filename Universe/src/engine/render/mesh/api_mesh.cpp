// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "api_mesh.h"


namespace engine::render::mesh
{
    obj* inst = nullptr;

    void init()
    {
        //
    }

    obj& get()
    {
        return *inst;
    }

    void term()
    {
        //
    }

}