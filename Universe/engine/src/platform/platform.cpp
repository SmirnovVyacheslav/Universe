// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/platform/platform.h"


namespace engine::platform
{
    class platform_impl : public platform
    {
        abstract_impl(platform_impl)

    public:
        platform_impl();
        platform_impl(platform_impl&& src) = delete;
        platform_impl(const platform_impl& src) = delete;

        platform_impl& operator=(platform_impl&& src) = delete;
        platform_impl& operator=(const platform_impl& src) = delete;

        ~platform_impl();

    private:
        //
    };
    platform_impl* inst = nullptr;


    void init()
    {
        delete inst;
        inst = new platform_impl;
    }


    platform_impl::platform_impl()
    {
        //
    }
    platform_impl::~platform_impl()
    {
        //
    }
}
