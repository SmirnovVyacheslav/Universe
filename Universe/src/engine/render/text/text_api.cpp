// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "text_api.h"
#include "text_impl.h"

namespace engine::render::text
{
    obj* inst = nullptr;


    void init()
    {
        term();
    }

    obj& add()
    {
        term();
        inst = new impl();
        return *inst;
    }

    void term()
    {
        delete inst;
        inst = nullptr;
    }
}
