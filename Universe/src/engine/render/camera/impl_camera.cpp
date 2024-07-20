// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_impl_camera.h"


namespace engine::render::camera
{
    impl::impl()
    {
        matrix_world = matrix_rotation_y(3.14159f / 4.0f);

        settings::obj settings_inst = settings::get();

        eye = { 0.0f, 3.0f, -5.0f };
        at = { 0.0f, 1.0f, 0.0f };
        up = { 0.0f, 1.0f, 0.0f };

        matrix_view = matrix_look_at(eye, at, up);
        matrix_projection = engine::matrix_projection(
            static_cast<float>(settings_inst.width) / static_cast<float>(settings_inst.height)
        );
    }

    matrix4 impl::world()
    {
        return matrix_world;
    }

    matrix4 impl::view()
    {
        return matrix_view;
    }

    matrix4 impl::projection()
    {
        return matrix_projection;
    }

    impl::~impl()
    {}
}
