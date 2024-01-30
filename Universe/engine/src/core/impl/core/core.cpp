// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/core/api/core.h"

#include "src/core/api/control.h"
#include "src/core/api/event.h"
#include "src/var/std.h"
#include "src/core/type/vertex.h"
#include "src/platform/api/core.h"
#include "src/platform/api/render.h"
#include "src/platform/api/render/shader.h"
#include "src/platform/api/render/vertex_buff.h"
#include "src/platform/api/render/index_buff.h"

#include "src/render/api.h"


namespace engine::core
{
    void init()
    {
        render::init();

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
        index_data[1] = 1;
        index_data[2] = 0;
        index_data[3] = 2;
        index_data[4] = 1;
        index_data[5] = 3;
        index_data[6] = 0;
        index_data[7] = 5;
        index_data[8] = 4;
        index_data[9] = 1;
        index_data[10] = 5;
        index_data[11] = 0;
        index_data[12] = 3;
        index_data[13] = 4;
        index_data[14] = 7;
        index_data[15] = 0;
        index_data[16] = 4;
        index_data[17] = 3;
        index_data[18] = 1;
        index_data[19] = 6;
        index_data[20] = 5;
        index_data[21] = 2;
        index_data[22] = 6;
        index_data[23] = 1;
        index_data[24] = 2;
        index_data[25] = 7;
        index_data[26] = 6;
        index_data[27] = 3;
        index_data[28] = 7;
        index_data[29] = 2;
        index_data[30] = 6;
        index_data[31] = 4;
        index_data[32] = 5;
        index_data[33] = 7;
        index_data[34] = 4;
        index_data[35] = 6;


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
