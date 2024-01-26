// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/render/settings/api.h"


namespace engine::render::settings
{
    obj* inst = nullptr;

    
    void init()
    {
        inst = new obj;
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
