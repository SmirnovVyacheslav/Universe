// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/render/device/api.h"
#include "src/render/device/device.h"


namespace engine::render::device
{
    class api_impl_t : public api_t
    {
        abstract_impl(api_impl_t)

    public:
        api_impl_t(const cfg_t* cfg);
        api_impl_t(api_impl_t&& src) = delete;
        api_impl_t(const api_impl_t& src) = delete;

        api_impl_t& operator=(api_impl_t&& src) = delete;
        api_impl_t& operator=(const api_impl_t& src) = delete;

        ~api_impl_t();

    private:
        device_t* device;
    };


    api_t* api_t::initialize(const cfg_t* cfg)
    {
        return new api_impl_t(cfg);
    }

    api_impl_t::api_impl_t(const cfg_t* cfg)
    {
        device = device_t::initialize(*cfg);
    }

    api_impl_t::~api_impl_t()
    {
        delete device;
    }
}
