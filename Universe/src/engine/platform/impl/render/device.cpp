// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/src/platform/impl/render/device.h"
#include "engine/src/platform/impl/render/directx/device_impl.h"


namespace engine::platform::render
{
    device* device_inst = nullptr;


    void init_device()
    {
        device_inst = new directx::device_impl();
    }

    void term_device()
    {
        delete device_inst;
    }

    void draw_device()
    {
        device_inst->draw();
    }

    shader::shader* init_shader(string file)
    {
        return device_inst->init_shader(file);
    }

    vertex_buff::vertex_buff* init_vertex_buff(vertex* data)
    {
        return device_inst->init_vertex_buff(data);
    }

    index_buff::index_buff* init_index_buff(uint16* data)
    {
        return device_inst->init_index_buff(data);
    }
}
