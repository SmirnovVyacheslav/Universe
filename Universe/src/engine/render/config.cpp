// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "config.h"

#include "engine/def/impl.h"
#include "engine/lib/ptr.h"

namespace engine::render::config
{
    class impl
    {
        impl_def

        int width  = 128;
        int height = 256;

        int refresh = 60;
    };


    ptr<impl> impl_inst;


    static int get_width()
    {
        return impl_inst->width;
    }
    static void set_width(int width)
    {
        impl_inst->width = width;
    }
    
    static int get_height()
    {
        return impl_inst->height;
    }
    static void set_height(int height)
    {
        impl_inst->height = height;
    }
    
    static int get_refresh()
    {
        return impl_inst->refresh;
    }
    static void set_refresh(int refresh)
    {
        impl_inst->refresh = refresh;
    }


    //
}
