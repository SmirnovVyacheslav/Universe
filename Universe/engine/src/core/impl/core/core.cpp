// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/core/api/core.h"

#include "src/core/api/control.h"
#include "src/core/api/event.h"
#include "src/core/type/std.h"
#include "src/core/type/vertex.h"
#include "src/platform/api/core.h"
#include "src/platform/api/render.h"
#include "src/platform/api/render/shader.h"
#include "src/platform/api/render/vertex_buff.h"
#include "src/platform/api/render/index_buff.h"


namespace engine::core
{
    void init()
    {
        platform::init();

        string basic_shaer = "game/res/shader/base.fx";
        vertex* vertex_data = new vertex[8];
        vertex_data[0] = vertex({ -1.0f, 1.0f, -1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f });
        vertex_data[1] = vertex({ 1.0f, 1.0f, -1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });
        vertex_data[2] = vertex({ 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f });
        vertex_data[3] = vertex({ -1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
        vertex_data[4] = vertex({ -1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });
        vertex_data[5] = vertex({ 1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f });
        vertex_data[6] = vertex({ 1.0f, -1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
        vertex_data[7] = vertex({ -1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 1.0f });
        uint16* index_data = new uint16[36];
        index_data[0] = 3;
        index_data[0] = 1;
        index_data[0] = 0;
        index_data[0] = 2;
        index_data[0] = 1;
        index_data[0] = 3;
        index_data[0] = 0;
        index_data[0] = 5;
        index_data[0] = 4;
        index_data[0] = 1;
        index_data[0] = 5;
        index_data[0] = 0;
        index_data[0] = 3;
        index_data[0] = 4;
        index_data[0] = 7;
        index_data[0] = 0;
        index_data[0] = 4;
        index_data[0] = 3;
        index_data[0] = 1;
        index_data[0] = 6;
        index_data[0] = 5;
        index_data[0] = 2;
        index_data[0] = 6;
        index_data[0] = 1;
        index_data[0] = 2;
        index_data[0] = 7;
        index_data[0] = 6;
        index_data[0] = 3;
        index_data[0] = 7;
        index_data[0] = 2;
        index_data[0] = 6;
        index_data[0] = 4;
        index_data[0] = 5;
        index_data[0] = 7;
        index_data[0] = 4;
        index_data[0] = 6;


        platform::render::shader::init(basic_shaer);
        platform::render::vertex_buff::init(vertex_data);
        platform::render::index_buff::init(index_data);
    }

    void exec()
    {
        control::start();

        while (control::status())
        {
            event::handle();
            platform::render::draw();
        }
    }

    void term()
    {
        platform::term();
    }
}
