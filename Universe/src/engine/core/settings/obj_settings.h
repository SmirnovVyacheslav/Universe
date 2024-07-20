// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_obj_settings.h"


#ifndef ENGINE_CORE_SETTINGS_OBJ
#define ENGINE_CORE_SETTINGS_OBJ

namespace engine::core::settings
{
    struct view
    {
        int32 width = 128;
        int32 height = 256;

        string name = u8"Engine";
    };

    struct obj
    {
        view view;
    };
}

#endif
