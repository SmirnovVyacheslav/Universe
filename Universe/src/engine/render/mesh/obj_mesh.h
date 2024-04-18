// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "engine/render/index/obj_index.h"
#include "engine/render/vertex/obj_vertex.h"
#include "engine/var/array.h"
#include "engine/var/std.h"
#include "engine/var/string.h"
#include "engine/var/vertex.h"


namespace engine::render::mesh
{
    class obj
    {
    public:
        obj(string file);
        obj(obj&& src) = delete;
        obj(const obj& src) = delete;

        void set();

        obj& operator=(obj&& src) = delete;
        obj& operator=(const obj& src) = delete;

        ~obj();
    private:
        index::obj* index_obj = nullptr;
        vertex::obj* vertex_obj = nullptr;

        array<uint16> load_index_data(string file);
        array<engine::vertex> load_vertex_data(string file);
    };
}
