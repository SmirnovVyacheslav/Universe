// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "api_vertex.h"

#include "directx/impl_vertex.h"


namespace engine::render::vertex
{
    obj* inst = nullptr;


    void init()
    {
        engine::vertex* vertex_data = new engine::vertex[8];
        vertex_data[0] = engine::vertex({ -1.0f, 1.0f, -1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f });
        vertex_data[1] = engine::vertex({ 1.0f, 1.0f, -1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });
        vertex_data[2] = engine::vertex({ 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f });
        vertex_data[3] = engine::vertex({ -1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
        vertex_data[4] = engine::vertex({ -1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });
        vertex_data[5] = engine::vertex({ 1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f });
        vertex_data[6] = engine::vertex({ 1.0f, -1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
        vertex_data[7] = engine::vertex({ -1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 1.0f });

        inst = new directx::impl(vertex_data);
    }

    obj& get()
    {
        return *inst;
    }

    void term()
    {
        delete inst;
        inst = nullptr;
    }
}
