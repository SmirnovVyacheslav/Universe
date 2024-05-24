// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_s_api_settings.h"


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
