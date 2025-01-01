// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "settings.h"

#include "engine/def/impl_def.h"
#include "engine/def/set_def.h"

#include "engine/var/sobj.h"

namespace engine::render::settings
{
    obj* inst = nullptr;


    obj& get()
    {
        if (!inst)
        {
            inst = new obj;
        }

        return *inst;
    }

    /*class impl
    {
        impl_def;

    public:
        struct
        {
            struct
            {
                string font   = u8"res/engine/font/";
                string shader = u8"res/engine/shader/";
            } engine;

            struct
            {
                string mesh   = u8"res/game/mesh/";
                string model  = u8"res/game/model/";
                string shader = u8"res/game/shader/";
            } game;
        } dir;

        struct
        {
            int32 width   = 128;
            int32 height  = 256;
            int32 refresh = 60;

            bool windowed = true;

        } view;
    };*/
}
