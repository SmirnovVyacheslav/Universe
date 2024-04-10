// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "engine/render/index/obj_index.h"
#include "engine/render/vertex/obj_vertex.h"
#include "engine/var/string.h"


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
    };
}
