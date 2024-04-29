// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "obj_mesh.h"

#include "engine/render/index/api_index.h"
#include "engine/render/vertex/api_vertex.h"
#include "engine/var/array.h"
#include "engine/var/std.h"
#include "engine/var/string.h"
#include "engine/var/vertex.h"


namespace engine::render::mesh
{
    class impl : public obj
    {
    public:
        impl(string file);
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

        array<uint16> load_index_data(string file);
        array<engine::vertex> load_vertex_data(string file);
    };
}