// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_s_api_mesh.h"


namespace engine::render::mesh
{
    obj* inst = nullptr;

    void init()
    {
        term();
    }

    obj& add(string file)
    {
        inst = new impl(file);
        return *inst;
    }

    void term()
    {
        delete inst;
        inst = nullptr;
    }

}