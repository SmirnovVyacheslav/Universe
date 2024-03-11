// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/core/def/abstract_class.h"
#include "engine/platform/api/render/shader.h"
#include "engine/platform/api/render/vertex_buff.h"
#include "engine/platform/api/render/index_buff.h"



namespace engine::platform::render
{
    abstract_class device
    {
        abstract_def(device)

        virtual void draw() = 0;

        virtual shader::shader* init_shader(string file) = 0;
        virtual vertex_buff::vertex_buff* init_vertex_buff(vertex* data) = 0;
        virtual index_buff::index_buff* init_index_buff(uint16* data) = 0;
    };

    void init_device();
    void term_device();

    void draw_device();

    shader::shader* init_shader(string file);
    vertex_buff::vertex_buff* init_vertex_buff(vertex* data);
    index_buff::index_buff* init_index_buff(uint16* data);
}
