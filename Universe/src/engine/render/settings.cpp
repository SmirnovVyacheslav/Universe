// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "settings.h"

namespace engine::render::settings
{
    obj* inst = nullptr;

    class impl : public obj
    {
    public:
        impl() = default;
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl() = default;
    };


    obj& get()
    {
        if (!inst)
        {
            inst = new impl;
        }

        return *inst;
    }
}
