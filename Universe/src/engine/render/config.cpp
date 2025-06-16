// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "config.h"

#include "engine/lib/ptr.h"

namespace engine::render::config
{
    class impl
    {
    public:
        impl()  = default;
        ~impl() = default;

        impl(impl&& src)      = delete;
        impl(const impl& src) = delete;

        impl& operator=(impl&& src)      = delete;
        impl& operator=(const impl& src) = delete;
    private:
        int width  = 128;
        int height = 256;

        int refresh = 60;
    };


    ptr<impl> impl_inst;

}
