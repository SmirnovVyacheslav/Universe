// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_api_render.h"


namespace engine::render
{
    void init()
    {
        camera::init();
        device::init();
        indices::init();
        vertices::init();
        shader::init();
        mesh::init();
        model::init();
        text::init();
    }

    void draw()
    {
        model::obj& model_obj = model::add(u8"cube");
        device::draw(model_obj);
    }

    void term()
    {
        text::term();
        model::term();
        mesh::term();
        shader::term();
        vertices::term();
        indices::term();
        device::term();
        camera::term();
    }
}
