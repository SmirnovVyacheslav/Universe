// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_h_impl_mesh.h"


#ifndef ENGINE_RENDER_MESH_IMPL
#define ENGINE_RENDER_MESH_IMPL

namespace engine::render::mesh
{
    class impl : public obj
    {
    public:
        impl(string name);
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        void set();
        int32 size();

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl();
    private:
        indices::obj& indices_obj;
        vertices::obj& vertices_obj;
    };
}

#endif
