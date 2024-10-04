// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "font_api.h"

namespace engine::render::font
{
    obj* inst = nullptr;


    void init()
    {
        term();

    }

    obj& get(string name)
    {
        return *inst;
    }

    void term()
    {
        delete inst;
        inst = nullptr;
    }
}
