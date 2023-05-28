// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/defines.h"
#include "src/core/data_type/std.h"


namespace engine
{
    // interface t_gdi_cfg
    struct t_gdi_cfg
    {
        int_32 mo_width = 128;
        int_32 mo_height = 256;
        int_32 mo_refresh = 60;

        bool mo_windowed = true;

        void* mp_window_handler;
    };
}
