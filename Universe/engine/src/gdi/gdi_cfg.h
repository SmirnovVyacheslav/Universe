// Copyright: (C) 2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/data_type/std.h"

namespace engine {
    class t_gdi_cfg {
    public:
        int_32 mo_width = 128;
        int_32 mo_height = 256;
        int_32 mo_refresh = 60;
        bool windowed = true;
        void* window_handler;
    };
}
