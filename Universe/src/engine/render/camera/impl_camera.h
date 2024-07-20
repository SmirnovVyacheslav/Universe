// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_impl_camera.h"


#ifndef ENGINE_RENDER_CAMERA_IMPL
#define ENGINE_RENDER_CAMERA_IMPL

namespace engine::render::camera
{
    class impl : public obj
    {
    public:
        impl();
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        matrix4 world();
        matrix4 view();
        matrix4 projection();

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl();
    private:
        vector3 eye = { 0.0f, 0.0f, 0.0f };
        vector3 at = { 0.0f, 0.0f, 0.0f };
        vector3 up = { 0.0f, 0.0f, 0.0f };

        matrix4 matrix_world = matrix_identity();
        matrix4 matrix_view = matrix_identity();
        matrix4 matrix_projection = matrix_identity();
    };
}

#endif
