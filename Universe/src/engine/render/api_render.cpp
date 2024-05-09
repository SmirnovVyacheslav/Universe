// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_s_api_render.h"


namespace engine::render
{
    void init()
    {
        settings::init();
        camera::init();
        device::init();
        index::init();
        vertex::init();
        shader::init();
        mesh::init();
        model::init();
    }

    void draw()
    {
        model::obj& model_obj = model::add(u8"cube");
        device::draw(model_obj);
    }

    void term()
    {
        model::term();
        mesh::term();
        shader::term();
        vertex::term();
        index::term();
        device::term();
        camera::term();
        settings::term();
    }
}
