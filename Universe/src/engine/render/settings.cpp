// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "settings.h"

namespace engine::render::settings
{
    obj* inst = nullptr;


    obj& get()
    {
        if (!inst)
        {
            inst = new obj;
        }

        return *inst;
    }
}
