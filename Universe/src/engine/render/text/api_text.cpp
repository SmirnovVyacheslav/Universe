// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_api_text.h"


namespace engine::render::text
{
    obj* inst = nullptr;


    void init()
    {
        term();
    }

    obj& add()
    {
        inst = nullptr;
        return *inst;
    }

    void term()
    {
        delete inst;
        inst = nullptr;
    }
}
