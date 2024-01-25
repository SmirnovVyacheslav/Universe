// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/render/src/camera/inc/api.h"
#include "src/render/src/camera/src/ext/inc/impl.h"


namespace engine::render::camera
{
    impl* inst = nullptr;


    void init()
    {
        inst = new impl;
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
