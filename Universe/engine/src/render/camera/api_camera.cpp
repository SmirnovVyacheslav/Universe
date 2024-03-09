// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/render/camera/api_camera.h"
#include "src/render/camera/impl_camera.h"


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
