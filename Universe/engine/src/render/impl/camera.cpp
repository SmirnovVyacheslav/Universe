// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/render/impl/camera.h"

#include "src/render/api/settings.h"
#include "src/core/type/vector3.h"
#include "src/core/type/matrix4.h"


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
        vector3 eye;
        vector3 at;
        vector3 up;

        matrix4 view;
        matrix4 projection;
    };

    impl::impl()
    {
        settings::obj settings_inst = settings::get();

        view = matrix_look_at(eye, at, up);
        projection = matrix_projection(
            static_cast<float>(settings_inst.width) / static_cast<float>(settings_inst.height)
        );
    }

    impl::~impl()
    {}


    impl* inst = nullptr;


    void init()
    {
        inst = new impl;
    }

    void term()
    {
        delete inst;
        inst = nullptr;
    }

    obj& get()
    {
        return *inst;
    }
}
