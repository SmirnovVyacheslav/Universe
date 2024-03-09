// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "impl_camera.h"

#include "render/settings/api_settings.h"


namespace engine::render::camera
{
    impl::impl()
    {
        settings::obj settings_inst = settings::get();

        eye = { 0.0f, 3.0f, -5.0f };
        at = { 0.0f, 1.0f, 0.0f };
        up = { 0.0f, 1.0f, 0.0f };

        view = matrix_look_at(eye, at, up);
        projection = matrix_projection(
            static_cast<float>(settings_inst.width) / static_cast<float>(settings_inst.height)
        );
    }

    impl::~impl()
    {}
}
