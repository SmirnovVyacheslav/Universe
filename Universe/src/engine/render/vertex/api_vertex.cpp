// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "engine/src/render/vertex/api_vertex.h"


namespace engine::render::vertex
{
    obj* inst = nullptr;


    void init()
    {
        //inst = new obj;
    }

    void term()
    {
        delete inst;
        inst = nullptr;
    }

    obj& get()
    {
        return *inst;
    }
}
