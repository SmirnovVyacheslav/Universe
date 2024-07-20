// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_api_settings.h"


namespace engine::core::settings
{
    obj* inst = nullptr;

    
    void init()
    {
        term();
        inst = new obj;
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
