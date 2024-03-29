// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "api_camera.h"

#include "engine/var/matrix4.h"
#include "engine/var/vector3.h"


namespace engine::render::camera
{
    class impl : public obj
    {
    public:
        impl();
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl();
    private:
        vector3 eye = { 0.0f, 0.0f, 0.0f };
        vector3 at = { 0.0f, 0.0f, 0.0f };
        vector3 up = { 0.0f, 0.0f, 0.0f };

        matrix4 view = matrix_identity();
        matrix4 projection = matrix_identity();
    };
}
