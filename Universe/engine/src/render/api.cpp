// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/render/api.h"
#include "src/render/device/cfg.h"
#include "src/render/device/api.h"
#include "src/platform/platform.h"


namespace engine::render
{
    class api_impl_t : public api_t
    {
        abstract_impl(api_impl_t)

    public:
        static api_impl_t* inst;

        api_impl_t();
        api_impl_t(api_impl_t&& src) = delete;
        api_impl_t(const api_impl_t& src) = delete;

        api_impl_t& operator=(api_impl_t&& src) = delete;
        api_impl_t& operator=(const api_impl_t& src) = delete;

        ~api_impl_t();

    private:
        device::api_t* device_api = nullptr;
        device::cfg_t device_cfg;
    };
    api_impl_t* api_impl_t::inst = nullptr;


    void api_t::initialize()
    {
        //delete api_impl_t::inst;
        api_impl_t::inst = new api_impl_t;
    }


    api_impl_t::api_impl_t()
    {
        //platform::window::create_window();
        device_cfg.window_handler = reinterpret_cast<void*>(platform::inst_def->id());
        device_api = device::api_t::initialize(&device_cfg);
    }
    api_impl_t::~api_impl_t()
    {
        delete device_api;
    }
}
