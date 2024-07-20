// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_api_view.h"


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
