// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/render/src/index/inc/api.h"


namespace engine::render::index
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
