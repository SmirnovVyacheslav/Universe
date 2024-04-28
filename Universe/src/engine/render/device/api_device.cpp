// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "api_device.h"

#include "directx/impl_device.h"


namespace engine::render::device
{
    obj* inst = nullptr;


    void init()
    {
        inst = new directx::impl();
    }

    void draw(mesh::obj& mesh_obj, shader::obj& shader_obj)
    {
        inst->draw(mesh_obj, shader_obj);
    }

    string type()
    {
        return "directx";
    }

    void term()
    {
        delete inst;
        inst = nullptr;
    }
}
