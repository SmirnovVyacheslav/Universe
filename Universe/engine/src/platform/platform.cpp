// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/platform/platform.h"
#include "src/platform/window/window.h"
#include "src/platform/window/config.h"


namespace engine::platform
{
    class platform_impl : public platform
    {
        abstract_impl(platform_impl)

    public:
        platform_impl();
        platform_impl(platform_impl&& src) = delete;
        platform_impl(const platform_impl& src) = delete;

        void* id();

        platform_impl& operator=(platform_impl&& src) = delete;
        platform_impl& operator=(const platform_impl& src) = delete;

        ~platform_impl();

    private:
        window::window* window_inst;
        window::config window_config;
    };
    platform_impl* inst = nullptr;
    platform* inst_def = nullptr;


    void init()
    {
        delete inst;
        inst = new platform_impl;
        inst_def = inst;
    }
    void term()
    {
        delete inst;
        inst = nullptr;
        inst_def = inst;
    }


    platform_impl::platform_impl()
    {
        window_inst = window::init(&window_config);
    }
    platform_impl::~platform_impl()
    {
        delete window_inst;
    }
    void* platform_impl::id()
    {
        return window_inst->id();
    }
}
