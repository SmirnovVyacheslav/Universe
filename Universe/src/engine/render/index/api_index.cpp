// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "api_index.h"


namespace engine::render::index
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
