// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "api_model.h"

#include "impl_model.h"


namespace engine::render::model
{
    obj* inst = nullptr;

    void init()
    {
        term();
    }

    obj& add(string name)
    {
        inst = new impl(name);
        return *inst;
    }

    void term()
    {
        delete inst;
        inst = nullptr;
    }

}