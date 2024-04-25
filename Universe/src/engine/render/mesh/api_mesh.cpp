// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "api_mesh.h"

#include "impl_mesh.h"


namespace engine::render::mesh
{
    obj* inst = nullptr;

    void init()
    {
        term();

    }

    void add(string file)
    {
        inst = new impl(file);
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