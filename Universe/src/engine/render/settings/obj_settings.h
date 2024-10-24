// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_obj_settings.h"


#ifndef ENGINE_RENDER_SETTINGS_OBJ
#define ENGINE_RENDER_SETTINGS_OBJ

namespace engine::render::settings
{
    struct dir
    {
        struct
        {
            string font = u8"res/engine/font/";
            string shader = u8"res/engine/shader/";
        } engine;
        
        struct
        {
            string mesh = u8"res/game/mesh/";
            string model = u8"res/game/model/";
            string shader = u8"res/game/shader/";
        } game;
    };

    struct obj
    {
        int32 width = 128;
        int32 height = 256;
        int32 refresh = 60;

        bool windowed = true;

        dir dir;
    };
}

#endif
