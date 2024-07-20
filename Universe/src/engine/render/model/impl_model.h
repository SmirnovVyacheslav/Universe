// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_impl_model.h"


#ifndef ENGINE_RENDER_MODEL_IMPL
#define ENGINE_RENDER_MODEL_IMPL

namespace engine::render::model
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
        mesh::obj& mesh_obj;
        shader::obj& shader_obj;
    };
}

#endif
