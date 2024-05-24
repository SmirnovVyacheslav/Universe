// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_s_api_view.h"


namespace engine::core::view
{
    obj* inst = nullptr;

    void init()
    {
        term();
        inst = new impl();
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
