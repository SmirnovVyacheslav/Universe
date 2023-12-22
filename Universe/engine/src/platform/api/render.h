// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/def/abstract_class.h"
#include "src/core/type/std.h"
#include "src/core/type/string.h"


namespace engine::platform::render
{
    struct render_config
    {
        int32 width = 128;
        int32 height = 256;
        int32 refresh = 60;

        bool windowed = true;
    };

    void init();
    void term();

    void draw();

    namespace vertex_buff
    {
        abstract_class vertex_buff
        {
            abstract_def(vertex_buff)

            int32 id;
        };

        add(string file);
        vertex_buff* get(int32 id);
        del(int32 id);
    }

    namespace index_buff
    {
        abstract_class index_buff
        {
            abstract_def(index_biff)

            int32 id;
        };

        add(string file);
        index_buff* get(int32 id);
        del(int32 id);
    }

    namespace vertex_layout
    {
        abstract_class vertex_layout
        {
            abstract_def(vertex_layout)

            int32 id;
        };

        add(string file);
        vertex_layout* get(int32 id);
        del(int32 id);
    }
}
