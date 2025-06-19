// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "config.h"

#include "engine/def/impl.h"
#include "engine/lib/ptr.h"

namespace engine::render::config
{
    class impl
    {
        impl_def

    private:
        int width  = 128;
        int height = 256;

        int refresh = 60;
    };


    ptr<impl> impl_inst;
}
