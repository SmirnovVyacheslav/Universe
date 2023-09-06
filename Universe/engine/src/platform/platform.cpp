// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/platform/api.h"


namespace engine::platform
{
    class impl : public api
    {
        abstract_impl(impl)

    public:
        static impl* inst;

        impl();
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl();

    private:
        //
    };
    impl* impl::inst = nullptr;


    void api::initialize()
    {
        delete impl::inst;
        impl::inst = new impl;
    }


    impl::impl()
    {
        //
    }
    impl::~impl()
    {
        //
    }
}
