// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "obj_mesh.h"

#include "engine/render/index/obj_index.h"
#include "engine/render/vertex/obj_vertex.h"
#include "engine/var/std.h"
#include "engine/var/string.h"


namespace engine::render::mesh
{
    class impl : public obj
    {
    public:
        impl(string mesh_name);
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        void set();
        int32 size();

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl();
    private:
        index::obj& index_obj;
        vertex::obj& vertex_obj;
    };
}
